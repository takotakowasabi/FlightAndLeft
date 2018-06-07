#pragma once
#include "Object.h"

class Bullet : public Object {
public:
	static const float DEFAULT_RADIUS;
	static const Vec2 DEFAULT_VELOCITY;
	static const Color DEFAULT_FRIEND_COLOR;

	Bullet(
		Vec2 position,
		ObjectGroup group,
		spFieldSize spFS,
		float radius = DEFAULT_RADIUS,
		Vec2 velocity = DEFAULT_VELOCITY,
		Color color = DEFAULT_FRIEND_COLOR
	);

	bool update() override;
	void draw() const override;

	void collision(const spObject) override;

private:
	Vec2 _velocity;

	Color _color;

	bool _deadFlag;

};