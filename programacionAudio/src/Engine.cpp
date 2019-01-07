#include "Engine.h"
#include <vector>

#ifndef LGFX_INCLUDED
#define LGFX_INCLUDED
#include "litegfx.h"
#endif


//TEXTURES

ltex_t *loadTexture(const char *filename) {

	ltex_t tex;
	ltex_t *texture = &tex;
	unsigned char *buffer;
	buffer = stbi_load(filename, &texture->width, &texture->height, nullptr, 4);

	texture = ltex_alloc(texture->width, texture->height, 1);
	ltex_setpixels(texture, buffer);

	stbi_image_free(static_cast<unsigned char *>(buffer));
	return texture;
}


ltex_t *loadTexture(const char *filename, uint8_t *buffer) {

	ltex_t tex;
	ltex_t *texture = &tex;
	buffer = stbi_load(filename, &texture->width, &texture->height, nullptr, 4);

	texture = ltex_alloc(texture->width, texture->height, 1);
	ltex_setpixels(texture, buffer);

	stbi_image_free(static_cast<unsigned char *>(buffer));
	return texture;
}



//MATH

bool valInInterval(float value, float a, float b){
	return value > a && value < b;
}


float clamp(float value, float low, float high) {
	if (value >= low && value <= high) return value;
	else if (value < low) return low;
	else if (value > high) return high;
}


float fract(float _value) {
	return _value - static_cast<int>(_value);
}
