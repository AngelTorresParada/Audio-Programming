#pragma once


#ifndef LGFX_INCLUDED
#define LGFX_INCLUDED
#include "litegfx.h"
#endif

#include "Vec2.h"
#include <stdint.h>


class Collider {
	public:
		virtual bool collides(const Collider& other) const = 0;
		virtual bool collides(const Vec2& circlePos, float circleRadius) const = 0;
		virtual bool collides(const Vec2& rectPos, const Vec2& rectSize) const = 0;
		virtual bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const = 0;

	protected:
		static bool checkCircleCircle(const Vec2& pos1, float radius1, const Vec2& pos2, float radius2);
		static bool checkCircleRect(const Vec2& circlePos, float circleRadius, const Vec2& rectPos, const Vec2& rectSize);
		static bool checkRectRect(const Vec2& rectPos1, const Vec2& rectSize1, const Vec2& rectPos2, const Vec2& rectSize2);
		static bool checkCirclePixels(const Vec2& circlePos, float circleRadius, const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels);
		static bool checkPixelsPixels(const Vec2& pixelsPos1, const Vec2& pixelsSize1, const uint8_t* pixels1, const Vec2& pixelsPos2, const Vec2& pixelsSize2, const uint8_t* pixels2);
		static bool checkPixelsRect(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels, const Vec2& rectPos, const Vec2& rectSize);


};



class RectCollider : public Collider {
	public:
		Vec2 origin;
		Vec2 size;

		RectCollider(const Vec2&, const Vec2&);
		~RectCollider();
		virtual bool collides(const Collider& other) const;
		virtual bool collides(const Vec2& circlePos, float circleRadius) const;
		virtual bool collides(const Vec2& rectPos, const Vec2& rectSize) const;
		virtual bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const;

	
};


class CircleCollider : public Collider {
	public:
		Vec2 center;
		float radius;

		CircleCollider(const Vec2&, float);
		~CircleCollider();
		virtual bool collides(const Collider& other) const;
		virtual bool collides(const Vec2& circlePos, float circleRadius) const;
		virtual bool collides(const Vec2& rectPos, const Vec2& rectSize) const;
		virtual bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const;
};



class PixelsCollider : public Collider {
	public:
		Vec2 origin;
		Vec2 size;
		const uint8_t *pixels;

		PixelsCollider(const Vec2&, const Vec2&, const uint8_t *);
		~PixelsCollider();
		virtual bool collides(const Collider& other) const;
		virtual bool collides(const Vec2& circlePos, float circleRadius) const;
		virtual bool collides(const Vec2& rectPos, const Vec2& rectSize) const;
		virtual bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* _pixels) const;
};