#include "Font.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

#ifndef LGFX_INCLUDED
#define LGFX_INCLUDED
#include "litegfx.h"
#endif

using namespace std;


Font::Font() {
}


Font::~Font() {
	
}


Font *Font::load(char *_filename, float _height) {
	Font *font = new Font();

	FILE *file = fopen(_filename, "rb");
	if (!file) return nullptr;
	else {
		fseek(file, 0, SEEK_END);
		size_t size = ftell(file);
		fseek(file, 0, SEEK_SET);
		size_t pixSize = 128;

		unsigned char *buffer = new unsigned char[size];

		fread(buffer, 1, size, file);
		fclose(file);

		std::vector<stbtt_bakedchar> charData(128);
		std::vector<unsigned char> pixels(pixSize * pixSize);
		std::vector<unsigned char> colorBuffer;

		while (stbtt_BakeFontBitmap(buffer, 0, _height, pixels.data(), pixSize, pixSize, 0, 128, charData.data()) <= 0) {
			pixSize *= 2;
			pixels.resize(pixSize * pixSize);
		}

		for (auto i = pixels.begin(); i != pixels.end(); i++) {
			colorBuffer.push_back(255);
			colorBuffer.push_back(255);
			colorBuffer.push_back(255);
			colorBuffer.push_back(*i);
		}

		lgfx_setblend(BLEND_ALPHA);
		ltex_t * tex = ltex_alloc(pixSize, pixSize, 0);
		ltex_setpixels(tex, colorBuffer.data());

		font->height = _height;
		font->texture = tex;
		font->texHeight = pixSize;
		font->texWidth = pixSize;
		font->charData = charData;

		delete buffer;
		charData.clear();
		pixels.clear();
		colorBuffer.clear();

		return font;
	}	
}

	

float Font::getHeight() const { return height; }

void Font::draw(const char *_text, const Vec2& _position) const {
	stbtt_aligned_quad *quad = new stbtt_aligned_quad();
	float x = _position.x;
	float y = _position.y;
	for (int i = 0; _text[i] != '\0'; i++) {
		char c = _text[i];
		int character = _text[i];
		stbtt_GetBakedQuad(charData.data(), texWidth, texHeight, character, &x, &y, quad, true);
		ltex_drawrotsized(texture, quad->x0, quad->y0, 0, 0, 0, (quad->x1 - quad->x0), (quad->y1 - quad->y0), quad->s0, quad->t0, quad->s1, quad->t1);
	}
}

void Font::Free() {
	ltex_free(texture);
	charData.clear();
}

Vec2 Font::getTextSize(const char *_text) const {
	stbtt_aligned_quad *quad = new stbtt_aligned_quad();
	float x = 0;
	float y = 0;
	float tWidth = 0;
	float tHeight = 0;

	for (int i = 0; _text[i] != '\0'; i++) {
		int character = _text[i];
		stbtt_GetBakedQuad(charData.data(), texWidth, texHeight, character, &x, &y, quad, true);
		float charHeight = abs(abs(quad->y1) - abs(quad->y0));
		if (_text[i + 1] == '\0') {
			tWidth = quad->x1;
		}
		if (charHeight > tHeight) {
			tHeight = charHeight;
		}
	}
	return Vec2(tWidth, tHeight);
}






