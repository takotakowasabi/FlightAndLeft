#pragma once
#include <memory>
#include <Siv3D.hpp>
#include "Field.h"

enum class ObjectGroup {
	neutral,
	friendObject,
	friendCharacter,
	enemyObject,
	enemyCharacter,
};

class Object;

using spObject = std::shared_ptr<Object>;

class Object
{
public:
	Object(Vec2 position, float radius, ObjectGroup group, spFieldSize _fieldSize);
	virtual ~Object() = default;

	virtual bool update() = 0;
	virtual void draw() const = 0;

	virtual void collision(const spObject) = 0;
	virtual Vec2 getPosition() {
		return _position;
	}
	virtual float getRadius() {
		return _radius;
	}
	ObjectGroup getGroup() {
		return _group;
	}
	bool isInvisible() {
		return _invisibleFlag;
	}

protected:
	Vec2 _position;
	float _radius;
	spFieldSize _spFieldSize;
	bool _invisibleFlag;

	bool isInFieldX();
	bool isInFieldY();
	bool isInField();

private:
	ObjectGroup _group;
};