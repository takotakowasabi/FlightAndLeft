#pragma once
#include <memory>
#include <Siv3D.hpp>

enum class ObjectGroup {
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
	Object(Vec2 position, float radius, ObjectGroup group);
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

protected:
	Vec2 _position;
	float _radius;

private:
	ObjectGroup _group;
};