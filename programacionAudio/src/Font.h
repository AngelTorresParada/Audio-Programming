#pragma once
#ifndef LGFX_INCLUDED
#define LGFX_INCLUDED
#include "litegfx.h"
#endif
#include "stb_truetype.h"
#include "Vec2.h"
#include <vector>

using std::vector;

class Font {
	public:
		Font();
		~Font();

		static Font *load(char *, float);
		float getHeight() const;
		Vec2 getTextSize(const char *) const;
		void draw(const char *, const Vec2&) const;
		void Free();


	private:
		ltex_t *texture;
		std::vector<stbtt_bakedchar> charData;
		float height;
		float texHeight;
		float texWidth;

};
