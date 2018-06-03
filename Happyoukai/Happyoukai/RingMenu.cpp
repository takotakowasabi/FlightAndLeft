#include "RingMenu.h"
#include <algorithm>

const int32 RingMenu::SIZE_A_CIRCLE = 6;
const float RingMenu::RADIUS_RATIO = 4.0f;
const int32 RingMenu::TRANSPARRENCY_MAX = 255;
const float RingMenu::AUTO_RALL_SPEED = 0.01f;

RingMenu::RingMenu(Vec2 leftUp, Vec2 size) :
	_leftUp(leftUp),
	_size(size),
	_font(),
	_radius(0),
	_center(),
	_nowAngle(0),
	_nowPart(0)
{
	_font = Font(static_cast<int32>(_size.y / 5), Typeface::Bold, FontStyle::Outline);
	_font.changeOutlineStyle({ HSV(210, 0.53, 0.75), Alpha(0), _size.y / 100 });
	_radius = _size.y / RADIUS_RATIO;
	_center = _leftUp + _size / 2;

//	addPart(L" ");
}

bool RingMenu::update()
{
//	for_each(_parts.begin(), _parts.end(), [](spRingMenuPart rmp) {
//		rmp->theta;
//	});
	float dif = calcDifference();
	if (mouseInMenu() && Mouse::Wheel()) {
		int32 wheel = Mouse::Wheel();
		for_each(_parts.begin(), _parts.end(), [wheel = wheel, this](spRingMenuPart rmp) {
			rmp->theta = calcRoll(rmp->theta, wheel / 10.0);
		});
		for_each(_parts.begin(), _parts.end(), [this](spRingMenuPart rmp) {
			rmp->transparrency = calcTransparrency(rmp->theta);
		});
	}
	else if (dif != 0){
		float rollAngle = 0;
		float absDif = abs(dif);
		int32 sign = dif / absDif;

		if (absDif <= AUTO_RALL_SPEED) rollAngle = dif;
		else rollAngle = AUTO_RALL_SPEED * sign;

		for_each(_parts.begin(), _parts.end(), [rollAngle = rollAngle](spRingMenuPart rmp) {
			rmp->theta += rollAngle;
		});
		for_each(_parts.begin(), _parts.end(), [this](spRingMenuPart rmp) {
			rmp->transparrency = calcTransparrency(rmp->theta);
		});
	}
	return isClicked();
}

void RingMenu::draw()
{
	Println(_nowPart);
	std::for_each(_parts.begin(), _parts.end(),
		[font = _font, radius = _radius, center = _center](spRingMenuPart rmp) {
		float drawY = center.y + cosf(rmp->theta - Pi) * radius;
		font(rmp->detail).drawCenter(center.x, drawY, Alpha(rmp->transparrency));
	});
}

size_t RingMenu::addPart(String&& str)
{
	size_t ret = _parts.size();
	_parts.push_back(std::make_shared<RingMenuPart>());
	_parts.back()->detail = str;
	_parts.back()->theta = calcRoll((1 - static_cast<float>(_parts.size()) / SIZE_A_CIRCLE) * 2 * Pi, -  Pi / 6);
	_nowPart = 0;
	_parts.back()->transparrency = calcTransparrency(_parts.back()->theta);
	return ret;
}

size_t RingMenu::pressedPart()
{
	return _nowPart;
}

bool RingMenu::mouseInMenu()
{
	Vec2 pos = Mouse::Pos() - _leftUp;
	return 0 < pos.x && pos.x < _size.x && 0 < pos.y && pos.y < _size.y;
}

int32 RingMenu::calcTransparrency(float theta)
{
	if (theta <= Pi) {
		return 0;
	}
	return static_cast<int32>((1 - (abs(Pi * 3 / 2 - theta) / (Pi / 2))) * TRANSPARRENCY_MAX);
}

float RingMenu::calcRoll(float theta, float rollAngle)
{
	theta += rollAngle;
	if (theta > 2 * Pi) {
		if (_nowPart == 5) _nowPart = 0;
		else ++_nowPart;
		return theta - 2 * Pi;
	}
	if (theta < 0) {
		if (_nowPart == 0) _nowPart = 5;
		else --_nowPart;
		return theta + 2 * Pi;
	}
	return theta;
}

float RingMenu::calcDifference()
{
	return (3 * Pi / 2) - _parts[_nowPart]->theta;
}

bool RingMenu::isClicked()
{
	return mouseInMenu() && Input::MouseL.clicked;
}
