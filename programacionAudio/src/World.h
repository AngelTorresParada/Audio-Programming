#pragma once

#ifndef LGFX_INCLUDED
#define LGFX_INCLUDED
#include "litegfx.h"
#endif

#include "Sprite.h"
#include "Vec2.h"

#include <vector>

class World {
	float clearRed;
	float clearGreen;
	float clearBlue;


	const ltex_t* back0;
	const ltex_t* back1;
	const ltex_t* back2; 
	const ltex_t* back3;


	float ratio0;
	float ratio1;
	float ratio2;
	float ratio3;


	Vec2 speed0;
	Vec2 speed1;
	Vec2 speed2;
	Vec2 speed3;


	Vec2 cameraPosition;


	Vec2 bkgDisplacement;
	Vec2 bkgSpeed;


	std::vector<Sprite *> spriteList;

	public:

		World(float, float, float, const ltex_t*, const ltex_t*, const ltex_t*, const ltex_t*);

		float getClearRed() const;
		float getClearGreen() const;
		float getClearBlue() const;


		const ltex_t* getBackground(size_t) const;

		float getScrollRatio(size_t) const;
		void setScrollRatio(size_t, float);

		const Vec2 &getScrollSpeed(size_t) const;
		void setScrollSpeed(size_t, const Vec2&);

		const Vec2 &getCameraPosition() const;
		void setCameraPosition(const Vec2&);

		const Vec2 &getBkgSpeed() const;
		void setBkgSpeed(const Vec2 &);

		void addSprite(Sprite&);
		void removeSprite(Sprite&);

		void update(float);
		void draw(const Vec2& screenSize);

};

