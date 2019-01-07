
#include <math.h>
#include "Vec2.h"


float x;
float y;


Vec2::Vec2(float m_x, float m_y) {
	x = m_x;
	y = m_y;
}


Vec2 Vec2::add(const Vec2& other) {
	Vec2 v(x + other.x, y + other.y);
	return v;
}


Vec2 Vec2::operator+(const Vec2& other) const {
	Vec2 v(x + other.x, y + other.y);
	return v;
}


Vec2 Vec2::operator+(float s) const {
	Vec2 v(x + s, y + s);
	return v;
}


Vec2 Vec2::substract(const Vec2& other) {
	Vec2 v(x - other.x, y - other.y);
	return v;
}


Vec2 Vec2::operator-(const Vec2& other) const {
	Vec2 v(x - other.x, y - other.y);
	return v;
}


Vec2 Vec2::operator-(float s) const {
	Vec2 v(x - s, y - s);
	return v;
}


Vec2 Vec2::multiply(const Vec2& other) {
	Vec2 v(x * other.x, y * other.y);
	return v;
}


Vec2 Vec2::multiplyByScalar(const float scalar) {
	Vec2 v(x * scalar, y * scalar);
	return v;
}


Vec2 Vec2::operator*(const Vec2& other) const {
	Vec2 v(x * other.x, y * other.y);
	return v;
}


Vec2 Vec2::operator*(float s) const {
	Vec2 v(x * s, y * s);
	return v;
}


Vec2 Vec2::divide(const Vec2& other) {
	Vec2 v(x / other.x, y / other.y);
	return v;
}


Vec2 Vec2::divideByScalar(const float scalar) {
	Vec2 v(x / scalar, y / scalar);
	return v;
}


Vec2 Vec2::operator/(const Vec2& other) const {
	Vec2 v(x / other.x, y / other.y);
	return v;
}


Vec2 Vec2::operator/(float s) const {
	Vec2 v(x / s, y / s);
	return v;
}




Vec2 Vec2::absolute() {
	float m_x = x;
	float m_y = y;

	if (m_x < 0) m_x *= -1;
	if (m_y < 0) m_y *= -1;

	Vec2 v(m_x, m_y);
	return v;
}


float Vec2::length() {
	return sqrt(pow(x, 2) + pow(y, 2));
}


Vec2 Vec2::normalize() {
	return length() != 0 ? divideByScalar(length()) : *this;
}



float Vec2::dot(const Vec2& other) {
	return x * other.x + y * other.y;
}


float Vec2::angle(const Vec2& other) const {
	return atan2(y - other.y, other.x - x);
}


float Vec2::distance(const Vec2 & other) const {
	return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
}


