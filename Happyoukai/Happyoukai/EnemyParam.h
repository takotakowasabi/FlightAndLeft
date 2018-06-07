#pragma once
#include <Siv3D.hpp>
#include "Enemy.h"
#include "Define.h"

class EnemyParam {
public:
	EnemyParam(Vec2 x, Vec2 v, size_t l = 1U, float r = static_cast<float>(WINDOW_WIDTH) / 80.0f) :
		life(l),
		position(x),
		velocity(v),
		radius(r)
	{
	}
	size_t life;
	Vec2 position;
	Vec2 velocity;
	float radius;
};