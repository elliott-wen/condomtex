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
#include "image.h"
#include <stdlib.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


#include <aconf.h>
#include <GString.h>
#include <gmem.h>
#include <gfile.h>


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





// --------------------------------------------------------------------




// // get the pagebox according to the pagebox_spec
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

void
read_pdf_info(integer img, char *page_name, int page_num,
              int pagebox_spec, int minor_pdf_version_wanted,
              int pdf_inclusion_errorlevel)
{

    float epdf_orig_x;
    float epdf_orig_y;
    float epdf_width;
    float epdf_height;
    float epdf_rotate;
    char *raw_image_filename = img_name(img);
    GString *filename = new GString(raw_image_filename);
    PDFDoc *doc = new PDFDoc(filename);
    
    if (!doc->isOk() || !doc->okToPrint()) 
    {
        pdftex_fail("Unable to analyse the input pdf %s\n", raw_image_filename);
    }

   

    float pdf_version_found, pdf_version_wanted;
    pdf_version_found = doc->getPDFVersion();
    pdf_version_wanted = 1 + (minor_pdf_version_wanted * 0.1);
    if (pdf_version_found > pdf_version_wanted + 0.01)
    {
        pdftex_fail("The version of this pdf is not supported %s (ver:%.1f)\n", raw_image_filename, pdf_version_found);
    }

    int pages_num_total = doc->getCatalog()->getNumPages();

    

    if (page_name) {
        // get page by name
        GString tmpname(page_name);
        LinkDest *link = doc->findDest(&tmpname);
        if (link == 0 || !link->isOk())
            pdftex_fail("PDF inclusion: invalid destination <%s>", page_name);
        Ref ref = link->getPageRef();
        page_num = doc->getCatalog()->findPage(ref.num, ref.gen);
        if (page_num == 0)
            pdftex_fail("PDF inclusion: destination is not a page <%s>",
                        page_name);
        delete link;
    } else {
        // get page by number
        if (page_num <= 0 || page_num > pages_num_total)
            pdftex_fail("PDF inclusion: required page does not exist <%i>",
                        pages_num_total);
    }

    Page *page = doc->getCatalog()->getPage(page_num);

    // get the pagebox (media, crop...) to use.
    PDFRectangle* pagebox = get_pagebox(page, pagebox_spec);
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

    


    epdf_rotate = page->getRotate() % 360;
    if (epdf_rotate < 0)
        epdf_rotate += 360;

    // page group
    if (page->getGroup() != NULL)
    {
        img_group_ref(img) = -1; 
    }
    else
    {
         img_group_ref(img) = 0;
    }

    pdf_ptr(img)->orig_x = epdf_orig_x;
    pdf_ptr(img)->orig_y = epdf_orig_y;
    pdf_ptr(img)->selected_page = page_num;
    pdf_ptr(img)->doc = doc;
    img_pages(img) = pages_num_total;
    img_width(img) = epdf_width;
    img_height(img) = epdf_height;
    img_rotate(img) = epdf_rotate;
}

// writes the current epf_doc.
// Here the included PDF is copied, so most errors that can happen during PDF
// inclusion will arise here.

void write_epdf(integer img)
{
    if(pdf_ptr(img)->doc != 0)
        delete(pdf_ptr(img)->doc);
    pdf_ptr(img)->doc = 0;
}



void epdf_delete(integer img)
{
   
}


