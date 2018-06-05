#include "RingMenu.h"
#include <algorithm>

const int32 RingMenu::SIZE_A_CIRCLE = 6;
const float RingMenu::RADIUS_RATIO = 4.0f;
const int32 RingMenu::TRANSPARRENCY_MAX = 255;
const float RingMenu::AUTO_RALL_SPEED = 0.01f;

RingMenu::RingMenu(Vec2 leftUp, Vec2 size) :
	_leftUp(leftUp),
	_size(size),
	_radius(0),
	_center(),
	_nowPart(0),
	_angleForLimit(0)
{
	for (int i = 0; i < SIZE_A_CIRCLE; i++) _parts.push_back(std::make_shared<RingMenuPart>());
	for (int i = 0; i < SIZE_A_CIRCLE; i++) addPart(L"");
	_partSize = 0;
//	_font = Font(static_cast<int32>(_size.y / 5), L"Palatino Linotype");
	_outline = Font(static_cast<int32>(_size.y / 5), L"Palatino Linotype", FontStyle::Outline);
	_outline.changeOutlineStyle({ HSV(210, 0.53, 0.75), Alpha(0), _size.y / 100 });
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
		float deltaAngle = wheel / 10.0;
		_angleForLimit += deltaAngle;

		if (_angleForLimit > Pi / 6 && _nowPart == _partSize - 1 && _nowPart < SIZE_A_CIRCLE - 1) { 
			_angleForLimit -= deltaAngle;
			deltaAngle = 0; 
		}
		else if (_angleForLimit > Pi / 6) _angleForLimit -= Pi / 3;
		else if (_angleForLimit < -Pi / 6 && _nowPart == 0 && _partSize < SIZE_A_CIRCLE ) {
			_angleForLimit -= deltaAngle;
			deltaAngle = 0;
		}
		else if (_angleForLimit < -Pi / 6) _angleForLimit += Pi / 3;

		for_each(_parts.begin(), _parts.end(), [deltaAngle = deltaAngle, this](spRingMenuPart rmp) {
			rmp->theta = calcRoll(rmp->theta, deltaAngle);
		});
		for_each(_parts.begin(), _parts.end(), [this](spRingMenuPart rmp) {
			rmp->transparrency = calcTransparrency(rmp->theta);
		});
	}
	else if (dif != 0){
		float deltaAngle = 0;
		float absDif = abs(dif);
		int32 sign = dif / absDif;

		if (absDif <= AUTO_RALL_SPEED) deltaAngle = dif;
		else deltaAngle = AUTO_RALL_SPEED * sign;

		_angleForLimit += deltaAngle;
		if (_angleForLimit > Pi / 6) _angleForLimit -= Pi / 3;
		else if (_angleForLimit < -Pi / 6) _angleForLimit += Pi / 3;

		for_each(_parts.begin(), _parts.end(), [deltaAngle = deltaAngle](spRingMenuPart rmp) {
			rmp->theta += deltaAngle;
		});
		for_each(_parts.begin(), _parts.end(), [this](spRingMenuPart rmp) {
			rmp->transparrency = calcTransparrency(rmp->theta);
		});
	}
//	Println(_angleForLimit);
	return isClicked();
}

void RingMenu::draw()
{
//	Println(_nowPart);
	std::for_each(_parts.begin(), _parts.end(),
		[outline = _outline, radius = _radius, center = _center](spRingMenuPart rmp) {
	/*	Println(rmp->detail);
		Println(rmp->theta);
		Println(rmp->transparrency);*/
		float drawY = center.y + cosf(rmp->theta - Pi) * radius;
//		font(rmp->detail).drawCenter(center.x, drawY, Color(87, 139, 193, rmp->transparrency));
		outline(rmp->detail).drawCenter(center.x, drawY, Alpha(rmp->transparrency));
	});
}

size_t RingMenu::addPart(String&& str)
{
	size_t ret = _partSize;
	_parts[ret]->detail = str;
	_parts[ret]->theta = calcRoll((1 - static_cast<float>(_partSize + 1) / SIZE_A_CIRCLE) * 2 * Pi, -  Pi / 6);
	_nowPart = 0;
	_parts[ret]->transparrency = calcTransparrency(_parts[ret]->theta);
	++_partSize;
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
