#pragma once
#include <Siv3D.hpp>
#include "Enemy.h"
#include "Define.h"

class EnemyParam {
public:
	EnemyParam(Texture text, Vec2 x, Vec2 v, Vec2 dir = Vec2(0.0, -1.0), size_t l = 1U, float r = static_cast<float>(WINDOW_WIDTH) / 80.0f) :
		texture(text),
		life(l),
		direction(dir),
		position(x),
		velocity(v),
		radius(r)
	{
	}
	Texture texture;
	size_t life;
	Vec2 position;
	Vec2 velocity;
	Vec2 direction;
	float radius;
};