#include "Bullet.h"

const float Bullet::DEFAULT_RADIUS = 5.0;
const Vec2 Bullet::DEFAULT_VELOCITY = Vec2(0.0, 5.0);
const Color Bullet::DEFAULT_FRIEND_COLOR = Color(216, 216, 68);

Bullet::Bullet(Vec2 position, ObjectGroup group, float radius, Vec2 velocity, Color color) :
	Object(position, radius, group),
	_velocity(velocity),
	_color(color)
{
}

bool Bullet::update()
{
	_position += _velocity;

	return false;
}

void Bullet::draw() const
{
	Ellipse(_position.x, _position.y, _radius, _radius * 2).draw(_color);
}

void Bullet::collision(const spObject)
{
}


