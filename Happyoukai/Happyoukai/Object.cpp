#include "Object.h"

Object::Object(Vec2 position, float radius, ObjectGroup group, spFieldSize fieldSize) :
	_position(position),
	_radius(radius),
	_spFieldSize(fieldSize),
	_invisibleFlag(false),
	_group(group)
{
}

bool Object::isInFieldX()
{
	if (_position.x + _radius < _spFieldSize->upLeft.x) return false;
	if (_position.x - _radius > _spFieldSize->downRight.x) return false;
	return true;
}

bool Object::isInFieldY()
{
	if (_position.y + _radius < _spFieldSize->upLeft.y) return false;
	if (_position.y - _radius > _spFieldSize->downRight.y) return false;
	return true;
}

bool Object::isInField()
{
	return isInFieldX() && isInFieldY();
}

