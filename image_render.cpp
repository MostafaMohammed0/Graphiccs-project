#include "main.h"
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <GL/stb_image.h>
#endif

void iG::IShowImage::BMP2(int x, int y, const char* filename, int ignoreColor)
{
	int  width, height, n;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* image = stbi_load(filename, &width, &height, &n, 4);
	glRasterPos2f(x, y);
	glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
	stbi_image_free(image);
}