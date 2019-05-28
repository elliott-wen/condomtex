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
LIBPNG  = $(LIBDIR)/libpng.a
LIBZLIB = $(LIBDIR)/libz.a
LIBMD5 = $(LIBDIR)/libmd5.a
LIBPDFTEX = $(LIBDIR)/libpdftex.a

sources = pdftex0.c pdftexini.c pdftex-pool.c pdftex-extra.c

objects = $(sources:.c=.o)

cpdfetex: $(headers) $(objects)
	$(CXX_LINK) $(objects) $(LIBPDFTEX) $(LIBXPDF) $(LIBZLIB) $(LIBMD5)

$(objects): %.o: %.c
	$(CC) -c $(CFLAGS) -I.  $< -o $@



clean:
	rm -f depend *.o
