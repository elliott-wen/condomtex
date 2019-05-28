/*
Copyright 1996-2017 Han The Thanh, <thanh@pdftex.org>

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

#include "ptexlib.h"
#include "image.h"
#include <endian.h>
#include <string.h>
//static int transparent_page_group = 0;

const unsigned char IHDRCHUNK[4] = {'I', 'H', 'D', 'R'};
struct  __attribute__ ((packed)) ChunkHeader{
    unsigned char signature[8];
    unsigned int len;
    unsigned char type[4];
    unsigned int width;
    unsigned int height;
    char bitdepth;
    char colortype;
    char idontcare1;
    char idontcare2;
    char idontcare3;
    char crc[4];
};

void read_png_info(integer img)
{
    FILE *png_file = xfopen(img_name(img), FOPEN_RBIN_MODE);
    png_ptr(img)->file = png_file;
    struct ChunkHeader header;
    int readNum = fread(&header,  1, sizeof(struct ChunkHeader), png_file);
    if(readNum != sizeof(struct ChunkHeader))
    {
        pdftex_fail("libpng: load header failed");
    }
    if(memcmp(header.type, IHDRCHUNK, 4) != 0)
    {
        pdftex_fail("libpng: bad header detected");
    }
    img_width(img) = be32toh(header.width);
    img_height(img) = be32toh(header.height);
    img_xres(img) = 0;
    img_yres(img) = 0;
    img_color(img) = IMAGE_COLOR_C;
    png_ptr(img)->bits_per_component = header.bitdepth;
//     if ((png_ptr(img) = png_create_read_struct(PNG_LIBPNG_VER_STRING,
//                                                NULL, NULL, warn)) == NULL)
//         pdftex_fail("libpng: png_create_read_struct() failed");
//     if ((png_info(img) = png_create_info_struct(png_ptr(img))) == NULL)
//         pdftex_fail("libpng: png_create_info_struct() failed");
//     if (setjmp(png_jmpbuf(png_ptr(img))))
//         pdftex_fail("libpng: internal error");
// #if PNG_LIBPNG_VER >= 10603
//     /* ignore possibly incorrect CMF bytes */
//     png_set_option(png_ptr(img), PNG_MAXIMUM_INFLATE_WINDOW, PNG_OPTION_ON);
// #endif
//     png_init_io(png_ptr(img), png_file);
//     png_read_info(png_ptr(img), png_info(img));
//     /* resolution support */
//     img_width(img) = png_get_image_width(png_ptr(img), png_info(img));
//     img_height(img) = png_get_image_height(png_ptr(img), png_info(img));
//     if (png_get_valid(png_ptr(img), png_info(img), PNG_INFO_pHYs)) {
//         img_xres(img) =
//             round(0.0254 *
//                   png_get_x_pixels_per_meter(png_ptr(img), png_info(img)));
//         img_yres(img) =
//             round(0.0254 *
//                   png_get_y_pixels_per_meter(png_ptr(img), png_info(img)));
//     }
//     switch (png_get_color_type(png_ptr(img), png_info(img))) {
//     case PNG_COLOR_TYPE_PALETTE:
//         img_color(img) = IMAGE_COLOR_C | IMAGE_COLOR_I;
//         break;
//     case PNG_COLOR_TYPE_GRAY:
//     case PNG_COLOR_TYPE_GRAY_ALPHA:
//         img_color(img) = IMAGE_COLOR_B;
//         break;
//     case PNG_COLOR_TYPE_RGB:
//     case PNG_COLOR_TYPE_RGB_ALPHA:
//         img_color(img) = IMAGE_COLOR_C;
//         break;
//     default:
//         pdftex_fail("unsupported type of color_type <%i>",
//                     png_get_color_type(png_ptr(img), png_info(img)));
//     }
    // if (fixedpdfminorversion >= 4
    //     && (png_get_color_type(png_ptr(img), png_info(img)) == PNG_COLOR_TYPE_GRAY_ALPHA
    //         || png_get_color_type(png_ptr(img), png_info(img)) == PNG_COLOR_TYPE_RGB_ALPHA)) {
    //      png with alpha channel in device colours; we have to add a Page
    //      * Group to make Adobe happy, so we have to create a dummy group object
         
    //     if (transparent_page_group == 0) {
    //         transparent_page_group = pdfnewobjnum();
    //     }
    //     if (pdfpagegroupval == 0) {
    //         pdfpagegroupval = transparent_page_group;
    //     }
    //     img_group_ref(img) = pdfpagegroupval;
    // }
}



void write_png(integer img)
{

}
