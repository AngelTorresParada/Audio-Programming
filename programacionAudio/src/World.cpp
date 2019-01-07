#include "World.h"

#include "Engine.h"


World::World(float _red = 0.15f, float _green = 0.15f, float _blue = 0.15f, 
	const ltex_t *_back0 = nullptr, const ltex_t *_back1 = nullptr, 
	const ltex_t *_back2 = nullptr, const ltex_t *_back3 = nullptr) {
	clearRed = _red;
	clearGreen = _green;
	clearBlue = _blue;

	back0 = _back0;
	back1 = _back1;
	back2 = _back2;
	back3 = _back3;

	spriteList.empty();

	cameraPosition = Vec2(0, 0);

	bkgDisplacement = Vec2(0, 0);
	bkgSpeed = Vec2(0, 0);

	lgfx_setorigin(cameraPosition.x, cameraPosition.y);
}

float World::getClearRed() const { return clearRed; }


float World::getClearGreen() const { return clearGreen; }


float World::getClearBlue() const { return clearBlue; }


const ltex_t * World::getBackground(size_t _layer) const {
	switch (_layer) {
		case 0: return back0;
		case 1: return back1;
		case 2: return back2;
		case 3: return back3;

	}
}


float World::getScrollRatio(size_t _layer) const {
	switch (_layer) {
		case 0: return ratio0;
		case 1: return ratio1;
		case 2: return ratio2;
		case 3: return ratio3;
	}
}


void World::setScrollRatio(size_t _layer, float _ratio) {
	switch (_layer) {
		case 0: 
			ratio0 = _ratio;
			break;
		case 1: 
			ratio1 = _ratio;
			break;
		case 2: 
			ratio2 = _ratio;
			break;
		case 3: 
			ratio3 = _ratio;
			break;
	}
}


const Vec2 &World::getScrollSpeed(size_t _layer) const {
	switch (_layer) {
		case 0: return speed0;
		case 1: return speed1;
		case 2: return speed2;
		case 3: return speed3;
	}
}


void World::setScrollSpeed(size_t _layer, const Vec2 &_speed) {
	switch (_layer) {
	case 0:
		speed0 = _speed;
		break;
	case 1:
		speed1 = _speed;
		break;
	case 2:
		speed2 = _speed;
		break;
	case 3:
		speed3 = _speed;
		break;
	}
}


const Vec2 &World::getCameraPosition() const{
	return cameraPosition;
}


void World::setCameraPosition(const Vec2 & _pos) {
	cameraPosition = _pos;
}


const Vec2 & World::getBkgSpeed() const { return bkgSpeed; }


void World::setBkgSpeed(const Vec2 &_speed){
	bkgSpeed = _speed;
}


void World::addSprite(Sprite & _sprite) {
	spriteList.push_back(&_sprite);
}

void World::removeSprite(Sprite & _sprite) {
	//spriteList.erase(&_sprite);
}


void World::update(float _deltaTime) {

	bkgDisplacement = bkgDisplacement - bkgSpeed * _deltaTime / Vec2(back3->width, back3->height);
	bkgDisplacement.x = fract(bkgDisplacement.x);
	bkgDisplacement.y = fract(bkgDisplacement.y);
	printf("%.2f, %.2f \n", bkgDisplacement.x, bkgDisplacement.y);

	for (auto s : spriteList) {
		s->update(_deltaTime);
	}
}

void World::draw(const Vec2 & screenSize) {
	lgfx_clearcolorbuffer(clearRed, clearGreen, clearBlue);

	ltex_drawrotsized(back3, -cameraPosition.x * ratio3, -cameraPosition.y * ratio3, 0, 0, 0, back0->width, back0->height,
		bkgDisplacement.x, bkgDisplacement.y,
		back0->width / back3->width + bkgDisplacement.x, back0->height / back3->height + bkgDisplacement.y);
	ltex_drawrotsized(back2, -cameraPosition.x * ratio2, -cameraPosition.y * ratio2, 0, 0, 0, back0->width, back2->height, 0, 0, back0->width / back2->width, 1);
	ltex_drawrotsized(back1, -cameraPosition.x * ratio1, -cameraPosition.y * ratio1, 0, 0, 0, back0->width, back1->height, 0, 0, back0->width / back1->width, 1);
	ltex_drawrotsized(back0, -cameraPosition.x * ratio0, -cameraPosition.y * ratio0, 0, 0, 0, back0->width, back0->height, 0, 0, 1, 1);

	for (auto s : spriteList) {
		s->draw();
	}
}
