#ifndef BMP_H_
#define BMP_H_

#include <stdint.h>

#pragma pack(push, 1)
typedef struct BITMAPFILEHEADER {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} bmp_header_file;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct BITMAPINFOHEADER {
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} bmp_header_info;
#pragma pack(pop)

typedef struct pixel {
    char rgb[3];
} pixel;

void delete_matrix(pixel **matrix, int m);

pixel** load_bmp(char *fin_name, bmp_header_file *header1, bmp_header_info *header2);

pixel** crop( pixel **image, int x, int y, int w, int h);

pixel** rotate(bmp_header_file *header1, bmp_header_info *header2, pixel **work_space, int w, int h);

void save_bmp(char *fout_name, bmp_header_file *header1, bmp_header_info *header2, pixel **pixels);

#endif