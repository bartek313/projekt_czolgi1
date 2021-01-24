#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define PNG_DEBUG 3
#include <png.h>

void read_png_file(char *filename, int *width, int *height,
		   png_byte * color_type,
		   png_byte * bit_depth, png_bytep ** row_pointers);
void write_png_file(char *filename, int width, int height,
		    png_byte color_type,
		    png_byte bit_depth, png_bytep * row_pointers);
void process_png_file(int width, int height, png_bytep * row_pointers);
png_bytep *create_image(int width, int height);
void init_png_file(int width, int height, png_bytep * row_pointers, char* mapa, png_bytep * row_pointers_grass, png_bytep * row_pointers_sand, png_bytep * row_pointers_wall);
void copy_tile(int xs, int ys, int width, int height,
	       png_bytep * row_pointers, png_bytep * row_pointers_from,
	       int idx);
