#! /bin/sh
# Written by Martin Schröder for pdfTeX. Public Domain.
#
# builds new pdftex binaries
# ----------
# try to find gnu make; we need it
MAKE=make;
if make -v 2>&1| grep -q "GNU Make" 
then 
  echo "Your make is a GNU-make; I will use that"
elif gmake -v >/dev/null 2>&1
then
  MAKE=gmake;
  echo "You have a GNU-make installed as gmake; I will use that"
else
  echo "I can't find a GNU-make; I'll try to use make and hope that works." 
  echo "If it doesn't, please install GNU-make."
fi
# ----------
# Options:
#       --make      : only make, no make distclean; configure
#       --parallel  : make -j 2 -l 3.0
ONLY_MAKE=FALSE
JOBS_IF_PARALLEL=2
MAX_LOAD_IF_PARALLEL=3.0
while [ "$1" != "" ] ; do
  if [ "$1" = "--make" ] ;
  then ONLY_MAKE=TRUE ;
  elif [ "$1" = "--parallel" ] ;
  then MAKE="$MAKE -j $JOBS_IF_PARALLEL -l $MAX_LOAD_IF_PARALLEL" ;
  fi ;
  shift ;
done
#
STRIP=strip
B=build
# ----------
# clean up, if needed
if [ -e "$B"/Makefile -a $ONLY_MAKE = "FALSE" ]
then
  rm -rf "$B"
elif [ ! -e "$B"/Makefile ]
then
    ONLY_MAKE=FALSE
fi
if [ ! -e "$B" ]
then
  mkdir "$B"
fi
#
cd "$B"
# clean up (uncomment the next line if you have commented out the rm and
# mkdir above)
# $MAKE distclean;
if [ "$ONLY_MAKE" = "FALSE" ]
then
  # do a configure without all the things we don't need
  echo "ignore warnings and errors about the main texmf tree"
  ../src/configure \
              --with-cxx-runtime-hack \
              --without-aleph     \
              --without-bibtex8   \
              --without-cjkutils  \
              --without-detex     \
              --without-dialog    \
              --without-dtl       \
              --without-dvi2tty   \
              --without-dvidvi    \
              --without-dviljk    \
              --without-dvipdfm   \
              --without-dvipdfmx  \
              --without-dvipng    \
              --without-dvipos    \
              --without-dvipsk    \
              --without-etex      \
              --without-gsftopk   \
              --without-lacheck   \
              --without-lcdf-typetools  \
              --without-makeindexk      \
              --without-mkocp-default   \
              --without-mkofm-default   \
              --without-musixflx  \
              --without-omega     \
              --without-pdfopen   \
              --without-ps2eps    \
              --without-ps2pkm    \
              --without-psutils   \
              --without-sam2p     \
              --without-seetexk   \
              --without-t1utils   \
              --without-tetex     \
              --without-tex4htk   \
              --without-texi2html \
              --without-texinfo   \
              --without-texlive   \
              --without-ttf2pk    \
              --without-tth       \
              --without-xdv2pdf   \
              --without-xdvik     \
              --without-xdvipdfmx \
              --without-xetex     \
              || exit 1 
fi
# make the binaries
(cd texk/web2c/web2c; $MAKE) || exit 1
(cd texk/web2c; $MAKE ../kpathsea/libkpathsea.la) || exit 1
(cd texk/web2c/lib; $MAKE) || exit 1
(cd texk/web2c; $MAKE pdftex pdfetex pdftosrc ttf2afm) || exit 1
# strip them
(cd texk/web2c; $STRIP pdf*tex pdftosrc ttf2afm)
# go back
cd ..
# show the results
d="$B"/texk/web2c
ls -l $d/pdf*tex $d/pdf*tex.pool $d/pdftosrc $d/ttf2afm
# vim: set syntax=sh ts=2: