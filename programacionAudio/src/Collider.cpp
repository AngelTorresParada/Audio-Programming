#include "Collider.h"
#include "Engine.h"
#include <string.h>


//COLLIDER MAIN CLASS

bool Collider::checkCircleCircle(const Vec2 & pos1, float radius1, const Vec2 & pos2, float radius2) {
	return (radius1 + radius2) > pos1.distance(pos2);
}

bool Collider::checkCircleRect(const Vec2 & circlePos, float circleRadius, const Vec2 & rectPos, const Vec2 & rectSize) {
	float closestX = clamp(circlePos.x, rectPos.x, rectPos.x + rectSize.x);
	float closestY = clamp(circlePos.y, rectPos.y, rectPos.y + rectSize.y);
	return circleRadius > circlePos.distance(Vec2(closestX, closestY));
}

bool Collider::checkRectRect(const Vec2 & rectPos1, const Vec2 & rectSize1, const Vec2 & rectPos2, const Vec2 & rectSize2) {
	return (valInInterval(rectPos1.x, rectPos2.x, rectPos2.x + rectSize2.x) || valInInterval(rectPos2.x, rectPos1.x, rectPos1.x + rectSize1.x)) &&
		(valInInterval(rectPos1.y, rectPos2.y, rectPos2.y + rectSize2.y) || valInInterval(rectPos2.y, rectPos1.y, rectPos1.y + rectSize1.y));
}

bool Collider::checkCirclePixels(const Vec2 & circlePos, float circleRadius, const Vec2 & pixelsPos, const Vec2 & pixelsSize, const uint8_t *pixels) {
	if (! checkCircleRect(circlePos, circleRadius, pixelsPos, pixelsSize)) return false;
	else {
		float x = pixelsPos.x;
		float y = pixelsPos.y;
		int size = static_cast<int>(pixelsSize.x * pixelsSize.y);
		for (int i = 0; i < size; i++) {
			if (*(pixels + i * 4 + 3) >= 128) {
				if (circlePos.distance(Vec2(x, y)) < circleRadius) {
					return true;
				}
			}
			x++;
			if (x >= pixelsPos.x + pixelsSize.x) {
				x = pixelsPos.x;
				y++;
			}
		}
		return false;
	}
}

bool Collider::checkPixelsPixels(const Vec2 & pixelsPos1, const Vec2 & pixelsSize1, const uint8_t * pixels1, const Vec2 & pixelsPos2, const Vec2 & pixelsSize2, const uint8_t * pixels2) {
	if (! checkRectRect(pixelsPos1, pixelsSize1, pixelsPos2, pixelsSize2)) return false;
	else {
		Vec2 origin1(pixelsPos1.x, pixelsPos1.y);
		Vec2 end1(pixelsPos1.x, pixelsPos1.y);

		//X inicial del área
		if (!valInInterval(pixelsPos1.x, pixelsPos2.x, pixelsPos2.x + pixelsSize2.x)) origin1.x = pixelsPos2.x;

		//X final del área
		if (pixelsPos1.x + pixelsSize1.x >= pixelsPos2.x + pixelsSize2.x) end1.x = pixelsPos2.x + pixelsSize2.x;
		else end1.x = pixelsPos1.x + pixelsSize1.x;

		//Y inicial del área
		if (!valInInterval(pixelsPos1.y, pixelsPos2.y, pixelsPos2.y + pixelsSize2.y)) origin1.y = pixelsPos2.y;

		//Y final del área
		if (pixelsPos1.y + pixelsSize1.y >= pixelsPos2.y + pixelsSize2.y) end1.y = pixelsPos2.y + pixelsSize2.y;
		else end1.y = pixelsPos1.y + pixelsSize1.y;


		Vec2 origin2(pixelsPos2.x, pixelsPos2.y);
		Vec2 end2(pixelsPos2.x, pixelsPos2.y);

		//X inicial del área
		if (!valInInterval(pixelsPos2.x, pixelsPos1.x, pixelsPos1.x + pixelsSize1.x)) origin2.x = pixelsPos1.x;

		//X final del área
		if (pixelsPos2.x + pixelsSize2.x >= pixelsPos1.x + pixelsSize1.x) end2.x = pixelsPos1.x + pixelsSize1.x;
		else end2.x = pixelsPos2.x + pixelsSize2.x;

		//Y inicial del área
		if (!valInInterval(pixelsPos2.y, pixelsPos1.y, pixelsPos1.y + pixelsSize1.y)) origin2.y = pixelsPos1.y;

		//Y final del área
		if (pixelsPos2.y + pixelsSize2.y >= pixelsPos1.y + pixelsSize1.y) end2.y = pixelsPos1.y + pixelsSize1.y;
		else end2.y = pixelsPos2.y + pixelsSize2.y;


		int originX1 = origin1.x - pixelsPos1.x;
		int originY1 = origin1.y - pixelsPos1.y;
		int endX1 = end1.x - pixelsPos1.x;
		int endY1 = end1.y - pixelsPos1.y;

		int originX2 = origin2.x - pixelsPos2.x;
		int originY2 = origin2.y - pixelsPos2.y;
		int endX2 = end2.x - pixelsPos2.x;
		int endY2 = end2.y - pixelsPos2.y;

		int x2 = originX2;
		int y2 = originY2;

		for (int y = originY1; y < endY1; y++) {
			for (int x = originX1; x < endX1; x++) {
				int pixel1 = (pixelsSize1.x * y + x) * 4 - 1;
				int pixel2 = (pixelsSize2.x * y2 + x2) * 4 - 1;
				if (*(pixels1 + pixel1) >= 128 && *(pixels2 + pixel2) >= 128) {
					return true;
				}
				x2++;
			}
			y2++;
			x2 = originX2;
		}
		return false;
	}
}

bool Collider::checkPixelsRect(const Vec2 & pixelsPos, const Vec2 & pixelsSize, const uint8_t * pixels, const Vec2 & rectPos, const Vec2 & rectSize) {
	if (!checkRectRect(pixelsPos, pixelsSize, rectPos, rectSize)) return false;
	else {
		Vec2 origin(pixelsPos.x, pixelsPos.y);
		Vec2 end(pixelsPos.x, pixelsPos.y);

		//X inicial del área
		if (!valInInterval(pixelsPos.x, rectPos.x, rectPos.x + rectSize.x)) origin.x = rectPos.x;	

		//X final del área
		if (pixelsPos.x + pixelsSize.x >= rectPos.x + rectSize.x) end.x = rectPos.x + rectSize.x;
		else end.x = pixelsPos.x + pixelsSize.x;

		//Y inicial del área
		if (!valInInterval(pixelsPos.y, rectPos.y, rectPos.y + rectSize.y)) origin.y = rectPos.y;

		//Y final del área
		if (pixelsPos.y + pixelsSize.y >= rectPos.y + rectSize.y) end.y = rectPos.y + rectSize.y;
		else end.y = pixelsPos.y + pixelsSize.y;


		int originX = origin.x - pixelsPos.x;
		int originY = origin.y - pixelsPos.y;
		int endX = end.x - pixelsPos.x;
		int endY = end.y - pixelsPos.y;


		for (int y = originY; y < endY; y++) {
			for (int x = originX; x < endX; x++) {
				int pixel = (pixelsSize.x * y + x) * 4 - 1;
				if (*(pixels + pixel) >= 128) {
					return true;
				}
			}
		}
		return false;
	}
}







//RECT COLLIDER

RectCollider::RectCollider(const Vec2& _origin, const Vec2& _size) {
	origin = _origin;
	size = _size;
}

RectCollider::~RectCollider() { }


bool RectCollider::collides(const Collider & other) const {
	return other.collides(origin, size);
}


bool RectCollider::collides(const Vec2 & circlePos, float circleRadius) const {
	return Collider::checkCircleRect(circlePos, circleRadius, origin, size);
}


bool RectCollider::collides(const Vec2 & rectPos, const Vec2 & rectSize) const {
	return Collider::checkRectRect(rectPos, rectSize, origin, size);
}


bool RectCollider::collides(const Vec2 & pixelsPos, const Vec2 & pixelsSize, const uint8_t * pixels) const {
	return Collider::checkPixelsRect(pixelsPos, pixelsSize, pixels, origin, size);
}







//CIRCLE COLLIDER

CircleCollider::CircleCollider(const Vec2& _center, float _radius) {
	center = _center;
	radius = _radius;
}


CircleCollider::~CircleCollider() { }


bool CircleCollider::collides(const Collider & other) const {
	return other.collides(center, radius);
}


bool CircleCollider::collides(const Vec2 & circlePos, float circleRadius) const {
	return Collider::checkCircleCircle(circlePos, circleRadius, center, radius);
}


bool CircleCollider::collides(const Vec2 & rectPos, const Vec2 & rectSize) const{
	return Collider::checkCircleRect(center, radius, rectPos, rectSize);
}


bool CircleCollider::collides(const Vec2 & pixelsPos, const Vec2 & pixelsSize, const uint8_t * pixels) const {
	return Collider::checkCirclePixels(center, radius, pixelsPos, pixelsSize, pixels);
}







//PIXELS COLLIDER

PixelsCollider::PixelsCollider(const Vec2& _origin, const Vec2& _size, const uint8_t *_pixels) {
	origin = _origin;
	size = _size;
	pixels = _pixels;
}


PixelsCollider::~PixelsCollider() { }


bool PixelsCollider::collides(const Collider & other) const {
	return other.collides(origin, size, pixels);
}


bool PixelsCollider::collides(const Vec2 & circlePos, float circleRadius) const {
	return Collider::checkCirclePixels(circlePos, circleRadius, origin, size, pixels);
}


bool PixelsCollider::collides(const Vec2 & rectPos, const Vec2 & rectSize) const{
	return Collider::checkPixelsRect(origin, size, pixels, rectPos, rectSize);
}


bool PixelsCollider::collides(const Vec2 & pixelsPos, const Vec2 & pixelsSize, const uint8_t * _pixels) const{
	return Collider::checkPixelsPixels(pixelsPos, pixelsSize, _pixels, origin, size, pixels);
}


