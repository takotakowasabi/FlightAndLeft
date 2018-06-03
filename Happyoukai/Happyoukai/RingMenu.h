#pragma once
#include <Siv3D.hpp>
#include <vector>
#include <memory>

struct RingMenuPart {
	String detail;
	float theta;
	int32 transparrency;
};

using spRingMenuPart = std::shared_ptr<RingMenuPart>;

class RingMenu {
public:
	static const int32 SIZE_A_CIRCLE;
	static const float RADIUS_RATIO;
	static const int32 TRANSPARRENCY_MAX;
	static const float AUTO_RALL_SPEED;

	RingMenu(Vec2 leftUp, Vec2 size);

	bool update();
	void draw();

	size_t addPart(String&& str);
	size_t pressedPart();

private:
	bool mouseInMenu();
	int32 calcTransparrency(float theta);
	float calcRoll(float theta, float rollAngle);
	float calcDifference();
	bool isClicked();

	std::vector<spRingMenuPart> _parts;
	Vec2 _leftUp;
	Vec2 _size;
	Font _font;

	float _radius;
	Vec2 _center;

	float _nowAngle;
	size_t _nowPart;
};