#include "Arrow.h"
#include "Define.h"

const int32 TravelArrow::ARROW_LENGTH = WINDOW_HEIGHT / 8;
const int32 TravelArrow::ARROW_WIDTH = WINDOW_HEIGHT / 12;

void TravelArrow::draw(const Vec2& travelDirection, const Vec2& playerPos) const
{
	Vec2 vec = playerPos + travelDirection * ARROW_LENGTH / 3;
	Line(vec, vec + travelDirection * ARROW_LENGTH).drawArrow(ARROW_WIDTH, Vec2(ARROW_WIDTH, ARROW_WIDTH), Color(248));
}
