#include "Cloud.h"
#include "Define.h"
#include <algorithm>

const float Cloud::CLOUD_RADIUS = static_cast<float>(WINDOW_HEIGHT) / 6;

Cloud::Cloud(Vec2 position, spFieldSize spFS, std::shared_ptr<Vec2> direct) :
	Object(position, CLOUD_RADIUS, ObjectGroup::neutral, spFS),
	_direct(direct),
	_drawFlag(false)
{
	int32 rand = Random(3, 5);
	float circlePosition = 0.f;
	float circleRadius = 0.f;
	for (int32 i = 0, posSign = 1; i < rand; i++) {
		circlePosition = posSign * ((i + 1) / 2) * 20;
		circleRadius = Random((3 - ((i + 1) / 2)) * 10, 40);
		_cloudCircles.push_back(floatPair(circlePosition, circleRadius));
	}
}

bool Cloud::update()
{
	_drawFlag = isInField();
	calcPos();
	return false;
}

void Cloud::draw() const
{
	if (_drawFlag) {
		Vec2 pos = _position;
		std::for_each(_cloudCircles.begin(), _cloudCircles.end(), [pos](floatPair fp) {
			Circle(pos.x + fp.first, pos.y, fp.second).draw(Color(248));
		});
	}
}

void Cloud::collision(spObject obj)
{
}

void Cloud::calcPos()
{
	_position -= *_direct * 2.0f;
	if (_position.y > LOOP_FIELD_HEIGHT) _position.y = 0;
	else if (_position.y < 0) _position.y = LOOP_FIELD_HEIGHT;
	if (_position.x > LOOP_FIELD_WIDTH) _position.x = 0;
	else if (_position.x < 0) _position.x = LOOP_FIELD_WIDTH;
}
