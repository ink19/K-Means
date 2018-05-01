#ifndef __K_MEANS_H
#define __K_MEANS_H 1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct __pixel_color_t{
    int color[3];
    int position;
    void *grouped;
    struct __pixel_color_t *next; 
} pixel_color_t;

typedef struct __group_t {
    int center_color[3];
    pixel_color_t member;
    struct __group_t *next;
} group_t;

extern int k_means_init(group_t *group_head, pixel_color_t **pixel_color_array, int k, int pixel_number, int *pixel_array);

extern int k_means_run(group_t *group_head, pixel_color_t *pixel_color_array, int pixel_number, int limit, int loop);

extern int k_means_color(group_t *group_head, pixel_color_t *pixel_color_array, int pixel_number, int *pixel_array);

extern int k_means_destroy(group_t *group_head, pixel_color_t *pixel_color_array);

static int k_means_get_center(group_t *group_head);

static int k_means_get_dis(int *a, int *b, int len);

#endif