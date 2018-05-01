#ifndef __JPEG_MANAGE_H
#define __JPEG_MANAGE_H 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jpeglib.h>
#include <jerror.h>

static void my_error_func(j_common_ptr error);

extern int jpeg_manage_file_to_memory(char *filename, JSAMPLE **jpeg_memory, int *width, int *height);
extern int jpeg_manage_memory_to_file(char *filename, JSAMPLE *jpeg_memory, int width, int height);

#endif