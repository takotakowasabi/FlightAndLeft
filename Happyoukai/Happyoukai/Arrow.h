#pragma once
#include <Siv3D.hpp>

class TravelArrow {
public:
	static const int32 ARROW_LENGTH;
	static const int32 ARROW_WIDTH;

	void draw(const Vec2& travelDirection, const Vec2& playerPos) const;
};