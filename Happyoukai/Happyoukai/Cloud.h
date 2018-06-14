#pragma once
#include <Siv3D.hpp>
#include "Object.h"
#include "Field.h"
#include <vector>

using floatPair = std::pair<float, float>;

class Cloud : public Object {
public:
	static const float CLOUD_RADIUS;

	Cloud(Vec2 position, spFieldSize spFS, std::shared_ptr<Vec2> direct);

	bool update() override;
	void draw() const override;

	void collision(spObject obj) override;

private:
	void calcPos();

	bool _drawFlag;
	std::shared_ptr<Vec2> _direct;
	std::vector<floatPair> _cloudCircles;
};