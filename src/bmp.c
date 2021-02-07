#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "bmp.h"

static int get_scans_size(int width) {
    if (width % 4 == 0) {
        return width * 3;
    }
    return width * 3 + 4 - (width * 3) % 4;
}

static pixel** create_matrix(int n, int m) {
    pixel **matrix = malloc(m * sizeof(pixel*));
    assert(matrix != NULL);
    for (int i = 0; i < m; i++) {
        matrix[i] = malloc(n);
        assert(matrix[i] != NULL);
    }
    return matrix;
}

void delete_matrix(pixel **matrix, int m) {
    for (int i = 0; i < m; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

pixel** load_bmp(char *fin_name, bmp_header_file *header1, bmp_header_info *header2) {
    FILE *fin = fopen(fin_name, "rb");
    assert(fin != NULL);
    fread(header1, sizeof(bmp_header_file), 1, fin);
    fread(header2, sizeof(bmp_header_info), 1, fin);
    int width = header2->biWidth;
    int height = header2->biHeight;
    int scans_size = get_scans_size(width);
    pixel **pixels = create_matrix(scans_size, height);
    for (int i = height - 1; i >= 0; i--) {
        fread(pixels[i], scans_size, 1, fin);
    }
    fclose(fin);
    return pixels;
}

pixel** crop(pixel **image, int x, int y, int w, int h) {
    pixel** work_space = create_matrix(w * sizeof(pixel), h);
    for (int i = 0; i < h; i++) {
        memcpy(work_space[i], image[y + i] + x, w * sizeof(pixel));
    }
    return work_space;
}

pixel** rotate(bmp_header_file *header1, bmp_header_info *header2, pixel **work_space, int w, int h) {
    int scans_size = get_scans_size(h);
    pixel **new_image = create_matrix(scans_size, w);
    char *tmp_pointer;
    int modulo = scans_size - h * 3;
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            new_image[i][j] = work_space[h - j - 1][i];
        }
        tmp_pointer = (char*)(new_image[i] + h);
        for (int j = 0; j < modulo; j++) {
            tmp_pointer[j] = 0;
        }
    }
    delete_matrix(work_space, h);
    header1->bfSize = 54 + h * w * 3 + modulo * w;
    header2->biSizeImage = header1->bfSize - 54;
    header2->biWidth = h;
    header2->biHeight = w;
    return new_image;
}

void save_bmp(char *fout_name, bmp_header_file *header1, bmp_header_info *header2, pixel **pixels) {
    FILE *fout = fopen(fout_name, "wb");
    assert(fout != NULL);
    int width = header2->biWidth;
    int height = header2->biHeight;
    int scans_size = get_scans_size(width);
    fwrite(header1, sizeof(bmp_header_file), 1, fout);
    fwrite(header2, sizeof(bmp_header_info), 1, fout);
    for (int i = height - 1; i >= 0; i--) {
        fwrite(pixels[i], scans_size, 1, fout);
    }
    delete_matrix(pixels, height);
    fclose(fout);
    return;
}