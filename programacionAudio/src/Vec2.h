#pragma once


class Vec2 {

public:
	float x;
	float y;

	Vec2(float x = 0, float y = 0);

	Vec2 add(const Vec2&);
	Vec2 operator+(const Vec2&) const;
	Vec2 operator+(float) const;
	Vec2 substract(const Vec2&);
	Vec2 operator-(const Vec2&) const;
	Vec2 operator-(float) const;
	Vec2 multiply(const Vec2&);
	Vec2 multiplyByScalar(const float);
	Vec2 operator*(const Vec2&) const;
	Vec2 operator*(float) const;
	Vec2 divide(const Vec2&);
	Vec2 divideByScalar(const float);
	Vec2 operator/(const Vec2&) const;
	Vec2 operator/(float) const;

	Vec2 absolute();
	float length();
	Vec2 normalize();

	float dot(const Vec2&);

	float angle(const Vec2&) const;
	float distance(const Vec2&) const;

};