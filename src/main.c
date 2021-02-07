#include <stdlib.h>
#include <string.h>
#include "bmp.h"

int main(int argc, char** argv) {
    if (argc <= 2) {
        return 1;
    }
    if (strcmp(argv[1], "crop-rotate") == 0) {
        if (argc < 8) {
            return 1;
        }
        bmp_header_file header1;
        bmp_header_info header2;
        bmp_header_file *ph1 = &header1;
        bmp_header_info *ph2 = &header2;
        int x = atoi(argv[4]);
        int y = atoi(argv[5]);
        int w = atoi(argv[6]);
        int h = atoi(argv[7]);
        if (x >= x + w || y >= y + h || x < 0 || y < 0 || w < 0 || h < 0) {
            return 1;
        }
        pixel **old_image = load_bmp(argv[2], ph1, ph2);
        if (x >= header2.biWidth || x + w > header2.biWidth || y >= header2.biHeight || y + h > header2.biHeight) {
            delete_matrix(old_image, header2.biHeight);
            return 1;
        }
        pixel **cropped_image = crop(old_image, x, y, w, h);
        delete_matrix(old_image, header2.biHeight);
        pixel **new_image = rotate(ph1, ph2, cropped_image, w, h);
        save_bmp(argv[3], ph1, ph2, new_image);
    }
    return 0;
}