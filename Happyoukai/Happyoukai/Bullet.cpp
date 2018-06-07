#include "Bullet.h"

const float Bullet::DEFAULT_RADIUS = 2.0;
const Vec2 Bullet::DEFAULT_VELOCITY = Vec2(0.0, -10.0);
const Color Bullet::DEFAULT_FRIEND_COLOR = Color(216, 216, 68);

Bullet::Bullet(Vec2 position, ObjectGroup group, spFieldSize spFS, float radius, Vec2 velocity, Color color) :
	Object(position, radius, group, spFS),
	_velocity(velocity),
	_color(color),
	_deadFlag(false)
{
}

bool Bullet::update()
{
	_position += _velocity;
	return !isInField() || _deadFlag;
}

void Bullet::draw() const
{
	Ellipse(_position.x, _position.y, _radius, _radius * 2).draw(_color);
}

void Bullet::collision(const spObject)
{
//	_deadFlag = true;
}


