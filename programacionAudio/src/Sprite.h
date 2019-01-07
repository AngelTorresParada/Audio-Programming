#pragma once

#ifndef LGFX_INCLUDED
#define LGFX_INCLUDED
#include "litegfx.h"
#endif
#include "Vec2.h"
#include "Collider.h"
#include <vector>


enum CollisionType {
	COLLISION_NONE,
	COLLISION_CIRCLE,
	COLLISION_RECT,
	COLLISION_PIXELS
};


class Sprite {

	typedef struct {
		float red;
		float green;
		float blue;
		float alpha;
	} Color;


	public:

		// Indicamos el número de frames en horizontal y vertical que tendrá la imagen del sprite
		Sprite(const ltex_t* tex, int hframes = 1, int vframes = 1);

		const ltex_t* getTexture() const;
		void setTexture(const ltex_t* tex);


		lblend_t getBlend() const;
		void setBlend(lblend_t mode);

		float getRed() const;
		float getGreen() const;
		float getBlue() const;
		float getAlpha() const;
		void setColor(float r, float g, float b, float a);

		const Vec2& getPosition() const;
		void setPosition(const Vec2& pos);

		float getAngle() const;
		void setAngle(float angle);

		const Vec2& getScale() const;
		void setScale(const Vec2& scale);


		// Tamaño de un frame multiplicado por la escala
		Vec2 getSize() const;


		// Este valor se pasa a ltex_drawrotsized en el pintado
		// para indicar el pivote de rotación
		const Vec2& getPivot() const;
		void setPivot(const Vec2& pivot);

		int getHframes() const;
		int getVframes() const;
		void setFrames(int _hframes, int _vframes);


		// Veces por segundo que se cambia el frame de animación
		int getFps() const;
		void setFps(int fps);


		// Frame actual de animación
		float getCurrentFrame() const;
		void setCurrentFrame(int frame);


		CollisionType getCollisionType() const;
		void setCollisionType(CollisionType type);


		const Collider *getCollider() const;


		void update(float deltaTime);
		void draw() const;
		bool collides(const Sprite& other) const;

	private:
		const ltex_t *texture;
		lblend_t blend;
		Color color;

		Vec2 position;
		float angle;
		Vec2 scale;

		Vec2 pivot;

		int Vframes;
		int Hframes;
		int fps;
		float currentFrame;

		std::vector<uint8_t> pixels;

		CollisionType colType;
		const Collider *collider;
};