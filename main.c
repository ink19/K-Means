#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jpeg_manage.h"
#include "k_means.h"
int mem2inta(JSAMPLE *jpeg_memory, int *int_array, int len);
int ina2mem(JSAMPLE *jpeg_memory, int *int_array, int len);

int main(int argc, char *argv[]) {
    if(argc < 3) {
        printf("usage: ./main inname outname\n");
        return 1;
    }
    JSAMPLE *jpeg_memory;
    int width, height, length;
    int *pix_array;
    group_t group_head;
    pixel_color_t *pixel_color_array;
    jpeg_manage_file_to_memory(argv[1], &jpeg_memory, &width, &height);
    length = width * height;
    pix_array = (int *)malloc(sizeof(int) * length * 3);
    mem2inta(jpeg_memory, pix_array, length * 3);

    k_means_init(&group_head, &pixel_color_array, 4, length, pix_array);

    k_means_run(&group_head, pixel_color_array, length, -1, 1000);

    k_means_color(&group_head, pixel_color_array, length, pix_array);

    ina2mem(jpeg_memory, pix_array, length * 3);

    jpeg_manage_memory_to_file(argv[2], jpeg_memory, width, height);

    free(jpeg_memory);
    k_means_destroy(&group_head, pixel_color_array);
}

int mem2inta(JSAMPLE *jpeg_memory, int *int_array, int len) {
    for(int loop_i = 0; loop_i < len; loop_i++) {
        *(int_array + loop_i) = *(jpeg_memory + loop_i);
    }
    return 0;
}

int ina2mem(JSAMPLE *jpeg_memory, int *int_array, int len) {
    for(int loop_i = 0; loop_i < len; loop_i++) {
        *(jpeg_memory + loop_i) = *(int_array + loop_i);
    }
    return 0;
}