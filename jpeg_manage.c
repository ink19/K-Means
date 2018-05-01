#include "jpeg_manage.h"

static void my_error_func(j_common_ptr error) {
    printf("%d\n", error->err->msg_code);
}

extern int jpeg_manage_file_to_memory(
    char *filename, 
    JSAMPLE **jpeg_memory, 
    int *width, 
    int *height
) {

    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *infile;
    JSAMPARRAY buffer;
    int row_stride;
    JSAMPLE *tmp_mem;
    
    cinfo.err = jpeg_std_error(&jerr);
    jerr.error_exit = my_error_func;
    jerr.output_message = my_error_func;
    jpeg_create_decompress(&cinfo);  
    infile = fopen(filename, "rb");
    if(infile == NULL) exit(1);
    jpeg_stdio_src(&cinfo, infile);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);
    row_stride = cinfo.output_width * cinfo.output_components;
    *width = cinfo.output_width;
    *height = cinfo.output_height;
    *jpeg_memory = (JSAMPLE *) malloc(sizeof(JSAMPLE) * (cinfo.output_height * cinfo.output_width * cinfo.output_components));
    tmp_mem = *jpeg_memory;
    buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
    while(cinfo.output_scanline < cinfo.output_height)  
    {  
        jpeg_read_scanlines (&cinfo, buffer, 1);
        memcpy(tmp_mem, buffer[0], sizeof(JSAMPLE) * row_stride);
        tmp_mem += row_stride;
    }
    jpeg_finish_decompress(&cinfo);

    jpeg_destroy_decompress(&cinfo);
    jpeg_destroy((j_common_ptr)&cinfo);

    fclose(infile);
}

extern int jpeg_manage_memory_to_file(
    char *filename, 
    JSAMPLE *jpeg_memory, 
    int width, 
    int height
) {
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    int row_stride = width * 3;
    FILE *outfile = NULL;
    JSAMPROW row_pointer[1];

    jerr.error_exit = my_error_func;
    jerr.output_message = my_error_func;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    outfile = fopen(filename, "wb");
    if(outfile == NULL) exit(1);
    jpeg_stdio_dest(&cinfo, outfile);
    cinfo.image_height = height;
    cinfo.image_width = width;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;
    jpeg_set_defaults(&cinfo);
    //jpeg_set_quality(&cinfo, 1, TRUE);
    jpeg_start_compress(&cinfo, TRUE);
    row_stride = width * cinfo.input_components;

    while (cinfo.next_scanline < cinfo.image_height)
    {
        row_pointer[0] = &jpeg_memory[cinfo.next_scanline * row_stride];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    fclose(outfile);
    return 0;
}