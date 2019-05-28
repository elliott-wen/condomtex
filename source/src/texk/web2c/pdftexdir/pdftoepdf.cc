/*
Copyright 1996-2016 Han The Thanh, <thanh@pdftex.org>

This file is part of pdfTeX.

pdfTeX is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

pdfTeX is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/* Do this early in order to avoid a conflict between
   MINGW32 <rpcndr.h> defining 'boolean' as 'unsigned char' and
   <kpathsea/types.h> defining Pascal's boolean as 'int'.
*/
#include <w2c/config.h>
#include <kpathsea/lib.h>

#include <stdlib.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#ifdef POPPLER_VERSION
#include <dirent.h>
#include <poppler-config.h>
#include <goo/GooString.h>
#include <goo/gmem.h>
#include <goo/gfile.h>
#define GString GooString
#else
#include <aconf.h>
#include <GString.h>
#include <gmem.h>
#include <gfile.h>
#endif
#include <assert.h>

#include "Object.h"
#include "Stream.h"
#include "Array.h"
#include "Dict.h"
#include "XRef.h"
#include "Catalog.h"
#include "Link.h"
#include "Page.h"
#include "GfxFont.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Error.h"

// This file is mostly C and not very much C++; it's just used to interface
// the functions of xpdf, which are written in C++.

extern "C" {
#include <pdftexdir/ptexmac.h>
#include <pdftexdir/pdftex-common.h>

// These functions from pdftex.web gets declared in pdftexcoerce.h in the
// usual web2c way, but we cannot include that file here because C++
// does not allow it.
extern int getpdfsuppresswarningpagegroup(void);
extern integer getpdfsuppressptexinfo(void);
extern integer zround(double);
}

// The prefix "PTEX" for the PDF keys is special to pdfTeX;
// this has been registered with Adobe by Hans Hagen.

#define pdfkeyprefix "PTEX"

#define MASK_SUPPRESS_PTEX_FULLBANNER 0x01
#define MASK_SUPPRESS_PTEX_FILENAME   0x02
#define MASK_SUPPRESS_PTEX_PAGENUMBER 0x04
#define MASK_SUPPRESS_PTEX_INFODICT   0x08

// PdfObject encapsulates the xpdf Object type,
// and properly frees its resources on destruction.
// Use obj-> to access members of the Object,
// and &obj to get a pointer to the object.
// It is no longer necessary to call Object::free explicitely.

class PdfObject {
  public:
    PdfObject() {               // nothing
    } ~PdfObject() {
        iObject.free();
    }
    Object *operator->() {
        return &iObject;
    }
    Object *operator&() {
        return &iObject;
    }
  private:                     // no copying or assigning
    PdfObject(const PdfObject &);
    void operator=(const PdfObject &);
  public:
    Object iObject;
};

// When copying the Resources of the selected page, all objects are copied
// recusively top-down. Indirect objects however are not fetched during
// copying, but get a new object number from pdfTeX and then will be
// appended into a linked list. Duplicates are checked and removed from the
// list of indirect objects during appending.

enum InObjType {
    objFont,
    objFontDesc,
    objOther
};

struct InObj {
    Ref ref;                    // ref in original PDF
    InObjType type;             // object type
    InObj *next;                // next entry in list of indirect objects
    int num;                    // new object number in output PDF
    fd_entry *fd;               // pointer to /FontDescriptor object structure
    int enc_objnum;             // Encoding for objFont
    int written;                // has it been written to output PDF?
};

struct UsedEncoding {
    int enc_objnum;
    GfxFont *font;
    UsedEncoding *next;
};

static InObj *inObjList;
static UsedEncoding *encodingList;
static GBool isInit = gFalse;

// --------------------------------------------------------------------
// Maintain list of open embedded PDF files
// --------------------------------------------------------------------

struct PdfDocument {
    char *file_name;
    PDFDoc *doc;
    XRef *xref;
    InObj *inObjList;
    int occurences;             // number of references to the document; the doc can be
    // deleted when this is negative
    PdfDocument *next;
};

static PdfDocument *pdfDocuments = 0;

static XRef *xref = 0;

// Returns pointer to PdfDocument record for PDF file.
// Creates a new record if it doesn't exist yet.
// xref is made current for the document.

static PdfDocument *find_add_document(char *file_name)
{
    PdfDocument *p = pdfDocuments;
    while (p && strcmp(p->file_name, file_name) != 0)
        p = p->next;
    if (p) {
        xref = p->xref;
        (p->occurences)++;
        return p;
    }
    p = new PdfDocument;
    p->file_name = xstrdup(file_name);
    p->xref = xref = 0;
    p->occurences = 0;
    GString *docName = new GString(p->file_name);
    p->doc = new PDFDoc(docName);       // takes ownership of docName
    if (!p->doc->isOk() || !p->doc->okToPrint()) {
        pdftex_fail("xpdf: reading PDF image failed");
    }
    p->inObjList = 0;
    p->next = pdfDocuments;
    pdfDocuments = p;
    return p;
}

// Deallocate a PdfDocument with all its resources

static void delete_document(PdfDocument * pdf_doc)
{
    PdfDocument **p = &pdfDocuments;
    while (*p && *p != pdf_doc)
        p = &((*p)->next);
    // should not happen:
    if (!*p)
        return;
    // unlink from list
    *p = pdf_doc->next;
    // free pdf_doc's resources
    InObj *r, *n;
    for (r = pdf_doc->inObjList; r != 0; r = n) {
        n = r->next;
        delete r;
    }
    xref = pdf_doc->xref;
    delete pdf_doc->doc;
    xfree(pdf_doc->file_name);
    delete pdf_doc;
}

// Replacement for
//      Object *initDict(Dict *dict1){ initObj(objDict); dict = dict1; return this; }

static void initDictFromDict(PdfObject & obj, Dict * dict)
{
    obj->initDict(xref);
    for (int i = 0, l = dict->getLength(); i < l; i++) {
        Object obj1;
        obj->dictAdd(copyString(dict->getKey(i)), dict->getValNF(i, &obj1));
    }
}

// --------------------------------------------------------------------




// get the pagebox according to the pagebox_spec
static PDFRectangle *get_pagebox(Page * page, int pagebox_spec)
{
    if (pagebox_spec == pdfboxspecmedia)
        return page->getMediaBox();
    else if (pagebox_spec == pdfboxspeccrop)
        return page->getCropBox();
    else if (pagebox_spec == pdfboxspecbleed)
        return page->getBleedBox();
    else if (pagebox_spec == pdfboxspectrim)
        return page->getTrimBox();
    else if (pagebox_spec == pdfboxspecart)
        return page->getArtBox();
    else
        pdftex_fail("PDF inclusion: unknown value of pagebox spec (%i)",
                    (int) pagebox_spec);
    return page->getMediaBox(); // to make the compiler happy
}


// Reads various information about the PDF and sets it up for later inclusion.
// This will fail if the PDF version of the PDF is higher than
// minor_pdf_version_wanted or page_name is given and can not be found.
// It makes no sense to give page_name _and_ page_num.
// Returns the page number.

int
read_pdf_info(char *image_name, char *page_name, int page_num,
              int pagebox_spec, int minor_pdf_version_wanted,
              int pdf_inclusion_errorlevel)
{
    PdfDocument *pdf_doc;
    Page *page;
    PDFRectangle *pagebox;
#ifdef POPPLER_VERSION
    int pdf_major_version_found, pdf_minor_version_found;
#else
    float pdf_version_found, pdf_version_wanted;
#endif
    // initialize
    if (!isInit) {
        globalParams = new GlobalParams();
        globalParams->setErrQuiet(gFalse);
        isInit = gTrue;
    }
    // open PDF file
    pdf_doc = find_add_document(image_name);
    epdf_doc = (void *) pdf_doc;

    // check PDF version
    // this works only for PDF 1.x -- but since any versions of PDF newer
    // than 1.x will not be backwards compatible to PDF 1.x, pdfTeX will
    // then have to changed drastically anyway.
#ifdef POPPLER_VERSION
    pdf_major_version_found = pdf_doc->doc->getPDFMajorVersion();
    pdf_minor_version_found = pdf_doc->doc->getPDFMinorVersion();
    if ((pdf_major_version_found > 1)
     || (pdf_minor_version_found > minor_pdf_version_wanted)) {
        const char *msg =
            "PDF inclusion: found PDF version <%d.%d>, but at most version <1.%d> allowed";
        if (pdf_inclusion_errorlevel > 0) {
            pdftex_fail(msg, pdf_major_version_found, pdf_minor_version_found, minor_pdf_version_wanted);
        } else if (pdf_inclusion_errorlevel < 0) {
            ; /* do nothing */
        } else { /* = 0, give warning */
            pdftex_warn(msg, pdf_major_version_found, pdf_minor_version_found, minor_pdf_version_wanted);
        }
    }
#else
    pdf_version_found = pdf_doc->doc->getPDFVersion();
    pdf_version_wanted = 1 + (minor_pdf_version_wanted * 0.1);
    if (pdf_version_found > pdf_version_wanted + 0.01) {
        char msg[] =
            "PDF inclusion: found PDF version <%.1f>, but at most version <%.1f> allowed";
        if (pdf_inclusion_errorlevel > 0) {
            pdftex_fail(msg, pdf_version_found, pdf_version_wanted);
        } else if (pdf_inclusion_errorlevel < 0) {
            ; /* do nothing */
        } else { /* = 0, give warning */
            pdftex_warn(msg, pdf_version_found, pdf_version_wanted);
        }
    }
#endif
    epdf_num_pages = pdf_doc->doc->getCatalog()->getNumPages();
    if (page_name) {
        // get page by name
        GString name(page_name);
        LinkDest *link = pdf_doc->doc->findDest(&name);
        if (link == 0 || !link->isOk())
            pdftex_fail("PDF inclusion: invalid destination <%s>", page_name);
        Ref ref = link->getPageRef();
        page_num = pdf_doc->doc->getCatalog()->findPage(ref.num, ref.gen);
        if (page_num == 0)
            pdftex_fail("PDF inclusion: destination is not a page <%s>",
                        page_name);
        delete link;
    } else {
        // get page by number
        if (page_num <= 0 || page_num > epdf_num_pages)
            pdftex_fail("PDF inclusion: required page does not exist <%i>",
                        epdf_num_pages);
    }
    // get the required page
    page = pdf_doc->doc->getCatalog()->getPage(page_num);

    // get the pagebox (media, crop...) to use.
    pagebox = get_pagebox(page, pagebox_spec);
    if (pagebox->x2 > pagebox->x1) {
        epdf_orig_x = pagebox->x1;
        epdf_width = pagebox->x2 - pagebox->x1;
    } else {
        epdf_orig_x = pagebox->x2;
        epdf_width = pagebox->x1 - pagebox->x2;
    }
    if (pagebox->y2 > pagebox->y1) {
        epdf_orig_y = pagebox->y1;
        epdf_height = pagebox->y2 - pagebox->y1;
    } else {
        epdf_orig_y = pagebox->y2;
        epdf_height = pagebox->y1 - pagebox->y2;
    }

    // get page rotation
    epdf_rotate = page->getRotate() % 360;
    if (epdf_rotate < 0)
        epdf_rotate += 360;

    // page group
    if (page->getGroup() != NULL)
        epdf_has_page_group = 1;    // only flag that page group is present;
                                    // the actual object number will be
                                    // generated in pdftex.web
    else
        epdf_has_page_group = 0;    // no page group present

    pdf_doc->xref = pdf_doc->doc->getXRef();
    return page_num;
}

// writes the current epf_doc.
// Here the included PDF is copied, so most errors that can happen during PDF
// inclusion will arise here.

void write_epdf(void)
{
    
}

// Called when an image has been written and it's resources in image_tab are
// freed and it's not referenced anymore.

void epdf_delete()
{
    PdfDocument *pdf_doc = (PdfDocument *) epdf_doc;
    xref = pdf_doc->xref;
    if (pdf_doc->occurences < 0) {
        delete_document(pdf_doc);
    }
}

// Called when PDF embedding system is finalized.
// Now deallocate all remaining PdfDocuments.

void epdf_check_mem()
{
    if (isInit) {
        PdfDocument *p, *n;
        for (p = pdfDocuments; p; p = n) {
            n = p->next;
            delete_document(p);
        }
        // see above for globalParams
        delete globalParams;
    }
}
