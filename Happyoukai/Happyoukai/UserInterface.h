#pragma once
#include <memory>
#include <Siv3D.hpp>
#include "Field.h"

class UserInterface {
public:
	virtual ~UserInterface() = default;

	virtual void update() = 0;
	virtual void draw() const = 0;

	virtual void transformStart(spFieldSize fieldSize, Vec2 direct) = 0;
	virtual void transform(int32 count) = 0;

private:
};

using spUI = std::shared_ptr<UserInterface>;