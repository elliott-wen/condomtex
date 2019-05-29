CC=gcc
CXX=g++
DEBUGFLAGS = -O2 -g
#DEBUGFLAGS = -ggdb -pg
CFLAGS = $(DEBUGFLAGS) -Wall $(XCFLAGS)
LDFLAGS =  $(DEBUGFLAGS)  $(XLDFLAGS)
CXX_LINK = $(CXX) -o $@ $(LDFLAGS)
#LIBS = -nodefaultlibs -Wl,-Bstatic -lstdc++ -Wl,-Bdynamic -lm -lgcc_eh -lgcc -lc -lglib-2.0
LIBS =  

texsources = pdftex0.c pdftexini.c pdftex-pool.c pdftex-extra.c memory.c fileop.c md5.c 

pdfsources = pdftexdir/avl.c pdftexdir/avlstuff.c \
		  pdftexdir/mapfile.c pdftexdir/utils.c pdftexdir/subfont.c pdftexdir/tounicode.c \
		  pdftexdir/vfpacket.c pdftexdir/writezip.c pdftexdir/writet3.c pdftexdir/writettf.c\
		  pdftexdir/writefont.c pdftexdir/writeimg.c pdftexdir/writejpg.c pdftexdir/writepng.c 


xpdfsources =  xpdf/FoFiBase.cc xpdf/FoFiEncodings.cc xpdf/FoFiIdentifier.cc \
    xpdf/FoFiTrueType.cc xpdf/FoFiType1.cc xpdf/FoFiType1C.cc\
	xpdf/FixedPoint.cc xpdf/gfile.cc xpdf/GHash.cc xpdf/GList.cc \
	xpdf/gmem.cc xpdf/gmempp.cc xpdf/GString.cc xpdf/AcroForm.cc \
	xpdf/PDF417Barcode.cc \
    xpdf/Annot.cc \
	xpdf/Array.cc \
	xpdf/BuiltinFont.cc \
	xpdf/BuiltinFontTables.cc \
	xpdf/CMap.cc \
	xpdf/Catalog.cc \
	xpdf/CharCodeToUnicode.cc \
	xpdf/Decrypt.cc \
	xpdf/Dict.cc \
	xpdf/Error.cc \
	xpdf/FontEncodingTables.cc \
	xpdf/Form.cc \
	xpdf/Function.cc \
	xpdf/Gfx.cc \
	xpdf/GfxFont.cc \
	xpdf/GfxState.cc \
	xpdf/GlobalParams.cc \
	xpdf/JArithmeticDecoder.cc \
	xpdf/JBIG2Stream.cc \
	xpdf/JPXStream.cc \
	xpdf/Lexer.cc \
	xpdf/Link.cc \
	xpdf/NameToCharCode.cc \
	xpdf/Object.cc \
	xpdf/OptionalContent.cc \
	xpdf/Outline.cc \
	xpdf/OutputDev.cc \
	xpdf/PDFDoc.cc \
	xpdf/PDFDocEncoding.cc \
	xpdf/PSTokenizer.cc \
	xpdf/Page.cc \
	xpdf/Parser.cc \
	xpdf/SecurityHandler.cc \
	xpdf/Stream.cc \
	xpdf/TextString.cc \
	xpdf/UnicodeMap.cc \
	xpdf/UnicodeRemapping.cc \
	xpdf/UTF8.cc \
	xpdf/XFAForm.cc \
	xpdf/XRef.cc \
	xpdf/Zoox.cc \
 	pdftexdir/pdftoepdf.cc

texobjects = $(texsources:.c=.o)

pdfobjects = $(pdfsources:.c=.o)

xpdfobjects = $(xpdfsources:.cc=.o)

pdftex: $(headers) $(texobjects) $(pdfobjects) $(xpdfobjects)
	$(CXX_LINK) $(texobjects) $(pdfobjects) $(xpdfobjects)

$(texobjects): %.o: %.c
	$(CC) -c $(CFLAGS) -I.  $< -o $@

$(pdfobjects): %.o: %.c
	$(CC) -c $(CFLAGS) -I.  $< -o $@

$(xpdfobjects): %.o: %.cc
	$(CC) -c $(CFLAGS) -I. -I xpdf/ $< -o $@

clean:
	rm -f depend pdftex *.o pdftexdir/*.o  xpdf/*.o
