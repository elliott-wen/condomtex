echo "Copying Static Libraries"
cp ../source/build-pdftex/texk/web2c/libpdftex.a .
cp ../source/build-pdftex/texk/web2c/libmd5.a .
cp ../source/build-pdftex/libs/xpdf/libxpdf.a .
cp ../source/build-pdftex/libs/libpng/libpng.a .
cp ../source/build-pdftex/libs/zlib/libz.a  .
echo "Copying PDFTEX Header Files"
mkdir -p pdftexdir
cp ../source/src/texk/web2c/pdftexdir/*.h pdftexdir/
echo "Copying web2c Files"
cp ../source/build-pdftex/texk/web2c/pdftexd.h .
cp ../source/build-pdftex/texk/web2c/pdftexcoerce.h .
cp ../source/build-pdftex/texk/web2c/pdftexini.c .
cp ../source/build-pdftex/texk/web2c/pdftex-pool.c .
cp ../source/build-pdftex/texk/web2c/pdftex0.c .
echo "Prepare Done!"