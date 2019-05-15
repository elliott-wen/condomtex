echo "Copying Static Libraries"
cp ../source/build-pdftex/texk/web2c/libpdftex.a ./libs/
cp ../source/build-pdftex/texk/web2c/libmd5.a ./libs/
cp ../source/build-pdftex/libs/xpdf/libxpdf.a ./libs/
cp ../source/build-pdftex/libs/libpng/libpng.a ./libs/
cp ../source/build-pdftex/libs/zlib/libz.a  ./libs/
echo "Copying PDFTEX Header Files"
mkdir -p pdftexdir
cp ../source/src/texk/web2c/pdftexdir/*.h pdftexdir/
echo "Copying web2c Files"
cp ../source/build-pdftex/texk/web2c/pdftexd.h .
cp ../source/build-pdftex/texk/web2c/pdftexcoerce.h .
cp ../source/build-pdftex/texk/web2c/pdftexini.c .
cp ../source/build-pdftex/texk/web2c/pdftex-pool.c .
cp ../source/build-pdftex/texk/web2c/pdftex0.c .
echo "Prepare Done! Prepare Compile"
echo "Compile Pdftex0"
gcc -g -O2 -O -c pdftex0.c  -I.
echo "Compile Pdftexini"
gcc -g -O2 -O -c pdftexini.c  -I.
echo "Compile PdftexPool"
gcc -g -O2 -O -c pdftex-pool.c  -I.
echo "Compile Extra"
gcc -g -O2 -O -c pdftex-extra.c -I.
echo "Compile Done"
g++ pdftex0.o pdftex-extra.o pdftexini.o pdftex-pool.o libs/libpdftex.a libs/libpng.a libs/libxpdf.a libs/libz.a libs/libmd5.a
