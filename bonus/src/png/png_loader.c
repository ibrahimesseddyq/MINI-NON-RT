#include "./../../../minirt.h"
#include <png.h>

bool	load_png(const char *filename, unsigned char **image_data, int *width, int *height)
{
	FILE *fp = fopen(filename, "rb");
	if (!fp)
		return (false);

	// Read and validate PNG signature
	png_byte header[8];
	fread(header, 1, 8, fp);
	if (png_sig_cmp(header, 0, 8)) {
		fclose(fp);
		return (false); // Not a PNG file
	}

	// Initialize PNG structures
	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		fclose(fp);
		return (false);
	}

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		fclose(fp);
		return (false);
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fclose(fp);
		return (false);
	}

	// Set up file input
	png_init_io(png_ptr, fp);
	png_set_sig_bytes(png_ptr, 8);

	// Read PNG info
	png_read_info(png_ptr, info_ptr);
	*width = png_get_image_width(png_ptr, info_ptr);
	*height = png_get_image_height(png_ptr, info_ptr);
	png_byte color_type = png_get_color_type(png_ptr, info_ptr);
	png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);

	// Adjustments for different color types
	if (bit_depth == 16)
		png_set_strip_16(png_ptr);
	if (color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png_ptr);
	if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
		png_set_expand_gray_1_2_4_to_8(png_ptr);
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png_ptr);
	if (color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_filler(png_ptr, 0xFF, PNG_FILLER_AFTER);
	if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png_ptr);

	// Update PNG info with transformations
	png_read_update_info(png_ptr, info_ptr);

	// Allocate memory for the image data
	png_size_t row_bytes = png_get_rowbytes(png_ptr, info_ptr);
	*image_data = (unsigned char*)malloc(row_bytes * (*height));
	if (!*image_data) {
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fclose(fp);
		return (false);
	}

	// Read the image data row by row
	png_bytep *row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * (*height));
	for (int y = 0; y < *height; y++)
		row_pointers[y] = *image_data + y * row_bytes;

	png_read_image(png_ptr, row_pointers);
	free(row_pointers);
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	fclose(fp);

	return (true);
}