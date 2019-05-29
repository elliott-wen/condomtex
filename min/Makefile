CC=gcc
CXX=g++
DEBUGFLAGS = -O2 -g
#DEBUGFLAGS = -ggdb -pg

CFLAGS = $(DEBUGFLAGS) -Wall $(XCFLAGS)
LDFLAGS =  $(DEBUGFLAGS)  $(XLDFLAGS)
CXX_LINK = $(CXX) -o $@ $(LDFLAGS)
#LIBS = -nodefaultlibs -Wl,-Bstatic -lstdc++ -Wl,-Bdynamic -lm -lgcc_eh -lgcc -lc -lglib-2.0
LIBS =  
LIBDIR = libs

LIBXPDF = $(LIBDIR)/libxpdf.a 
LIBPDFTEX = $(LIBDIR)/libpdftex.a

ansicsources = pdftex0.c pdftexini.c pdftex-pool.c pdftex-extra.c memory.c fileop.c md5.c \
		  pdftexdir/avl.c pdftexdir/avlstuff.c \
		  pdftexdir/mapfile.c pdftexdir/utils.c pdftexdir/subfont.c pdftexdir/tounicode.c \
		  pdftexdir/vfpacket.c pdftexdir/writezip.c pdftexdir/writet3.c \
		  pdftexdir/writefont.c pdftexdir/writeimg.c pdftexdir/writejpg.c pdftexdir/writepng.c 

cppsources = pdftexdir/pdftoepdf.cc

ansicobjects = $(ansicsources:.c=.o)

cppobjects = $(cppsources:.cc=.o)

cpdfetex: $(headers) $(ansicobjects) $(cppobjects)
	$(CXX_LINK) $(ansicobjects) $(cppobjects) $(LIBXPDF) 

$(ansicobjects): %.o: %.c
	$(CC) -c $(CFLAGS) -I.  $< -o $@

$(cppobjects): %.o: %.cc
	$(CXX) -c $(CFLAGS) -I.  $< -o $@

clean:
	rm -f depend *.o pdftexdir/*.o
