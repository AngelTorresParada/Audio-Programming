
#ifndef LGFX_INCLUDED
#define LGFX_INCLUDED
#include "litegfx.h"
#endif

#include "Sprite.h"
#include "Collider.h"
#include "Engine.h"





Sprite::Sprite(const ltex_t * _tex, int _hframes, int _vframes) {
	texture = _tex;
	Hframes = _hframes;
	Vframes = _vframes;
	blend = BLEND_ALPHA;
	position = Vec2(0, 0);
	scale = Vec2(1, 1);
	pivot = Vec2(0.5f, 0.5f);
	currentFrame = 0;
	color.red = 1; color.green = 1; color.blue = 1; color.alpha = 1;
	colType = COLLISION_NONE;
	
	size_t size = texture->width * texture->height;
	std::vector<uint8_t> pixes(size * 4);
	ltex_getpixels(texture, pixes.data());
	pixels = pixes;
}


const ltex_t * Sprite::getTexture() const { return texture; }
void Sprite::setTexture(const ltex_t * _tex) { texture = _tex; }


lblend_t Sprite::getBlend() const { return blend; }
void Sprite::setBlend(lblend_t _mode) { blend = _mode; }


float Sprite::getRed() const { return color.red; }
float Sprite::getGreen() const { return color.green; }
float Sprite::getBlue() const { return color.blue; }
float Sprite::getAlpha() const { return color.alpha; }
void Sprite::setColor(float r, float g, float b, float a) {
	color.red = r;
	color.green = g;
	color.blue = b;
	color.alpha = a;
}


const Vec2 & Sprite::getPosition() const { return position; }
void Sprite::setPosition(const Vec2 & pos) { position = pos;  }


float Sprite::getAngle() const { return angle; }
void Sprite::setAngle(float _angle) { angle = _angle; }


const Vec2 & Sprite::getScale() const { return scale; }
void Sprite::setScale(const Vec2 & _scale) { scale = _scale; }


Vec2 Sprite::getSize() const { return Vec2(texture->width / static_cast<float>(Hframes), texture->height / static_cast<float>(Vframes)) * scale; }


const Vec2 & Sprite::getPivot() const { return pivot; }
void Sprite::setPivot(const Vec2 & _pivot) { pivot = _pivot; }


int Sprite::getHframes() const { return Hframes; }


int Sprite::getVframes() const { return Vframes; }


void Sprite::setFrames(int _hframes, int _vframes)
{
	Hframes = _hframes;
	Vframes = _vframes;
}


int Sprite::getFps() const { return fps; }
void Sprite::setFps(int _fps) { fps = _fps; }


float Sprite::getCurrentFrame() const { return currentFrame; }
void Sprite::setCurrentFrame(int _frame) { currentFrame = _frame; }


CollisionType Sprite::getCollisionType() const { return colType; }


void Sprite::setCollisionType(CollisionType type) { 
	colType = type; 
	if (collider) delete collider;
	switch (colType) {
		case COLLISION_CIRCLE:
			collider = new CircleCollider(position, getSize().y / 2);
			break;
		case COLLISION_RECT:
			collider = new RectCollider(position - getSize() / 2, getSize());
			break;
		case COLLISION_PIXELS:
			collider = new PixelsCollider(position - getSize() / 2, getSize(), pixels.data());
			break;
	}

}


const Collider * Sprite::getCollider() const { return collider; }


void Sprite::update(float deltaTime) {
	int numFrames = Hframes * Vframes;
	currentFrame += deltaTime * fps;
	if (currentFrame >= numFrames) currentFrame -= numFrames;
	setCollisionType(getCollisionType());
}


void Sprite::draw() const {
	float u0 = (static_cast<int>(currentFrame) % Hframes + 0.0f) / (Hframes * 1.0f);
	float v0 = static_cast<int>(currentFrame / Vframes + 0.0f) / (Vframes * 1.0f);
	float u1 = ((static_cast<int>(currentFrame) % Hframes) + 1.0f) / (Hframes * 1.0f);
	float v1 = (static_cast<int>(currentFrame / Vframes) + 1.0f) / (Vframes * 1.0f);

	lgfx_setblend(blend);
	lgfx_setcolor(color.red, color.green, color.blue, color.alpha);
	ltex_drawrotsized(texture, position.x, position.y, angle, pivot.x, pivot.y, getSize().x, getSize().y, u0, v0, u1, v1);
}


bool Sprite::collides(const Sprite & other) const {
	return collider->collides(*other.collider);
}



