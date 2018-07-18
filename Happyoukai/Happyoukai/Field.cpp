#include "Field.h"
#include "Define.h"

const Vec2 Field::DEFAULT_UPLEFT = Vec2(WINDOW_WIDTH / 9, WINDOW_HEIGHT / 16);
const Vec2 Field::DEFAULT_DOWNRIGHT = Vec2(WINDOW_WIDTH * 2 / 3, WINDOW_HEIGHT * 15 / 16);

Field::Field(Vec2 upLeft, Vec2 downRight) :
	_transformFlag(false),
	_nowDirect(Vec2(0.0, -1.0)),
	_transformCount(0)
{
	_fieldSize = std::make_shared<FieldSize>();
	_fieldSize->upLeft = upLeft;
	_fieldSize->downRight = downRight;

	_goalFieldSize = std::make_shared<FieldSize>();
	_goalFieldSize->upLeft = upLeft;
	_goalFieldSize->downRight = downRight;
}

void Field::update()
{
	if (_transformCount) {
		Vec2 deltaUL = _goalFieldSize->upLeft - _fieldSize->upLeft;
		Vec2 deltaDR = _goalFieldSize->downRight - _fieldSize->downRight;
		deltaUL /= _transformCount;
		deltaDR /= _transformCount;
		_fieldSize->upLeft += deltaUL;
		_fieldSize->downRight += deltaDR;
		--_transformCount;
	}
}

void Field::draw()
{
	Graphics2D::SetStencilState(StencilState::Replace);
	Graphics2D::SetStencilValue(1);

	Vec2 size = _fieldSize->downRight - _fieldSize->upLeft;
	RoundRect(_fieldSize->upLeft.x, _fieldSize->upLeft.y, size.x, size.y, WINDOW_HEIGHT / 16).draw();

	Graphics2D::SetStencilState(StencilState::None);
}

void Field::transform(const Vec2& centerPos, const Vec2& direct)
{
	Vec2 center = centerPos;
	if (direct.x == 0 && _nowDirect.x == 0) return;
	if (direct.y == 0 && _nowDirect.y == 0) return;

	if (direct.y == 0) {
		if (center.y < WINDOW_HEIGHT * 1 / 3) center.y = WINDOW_HEIGHT * 1 / 3;
		else if (center.y > WINDOW_HEIGHT * 2 / 3) center.y = WINDOW_HEIGHT * 2 / 3;

		_goalFieldSize->upLeft = Vec2(WINDOW_WIDTH / 16, center.y - WINDOW_HEIGHT * 5 / 18);
		_goalFieldSize->downRight = Vec2(WINDOW_WIDTH * 15 / 16, center.y + WINDOW_HEIGHT * 5 / 18);
	}
	else if (direct.x == 0) {
		if (center.x < WINDOW_WIDTH * 1 / 3) center.x = WINDOW_WIDTH * 1 / 3;
		else if (center.x > WINDOW_WIDTH * 2 / 3) center.x = WINDOW_WIDTH * 2 / 3;

		_goalFieldSize->upLeft = Vec2(center.x - WINDOW_WIDTH * 5 / 18, WINDOW_HEIGHT / 16);
		_goalFieldSize->downRight = Vec2(center.x + WINDOW_WIDTH * 5 / 18, WINDOW_HEIGHT * 15 / 16);
	}
	_transformCount = CHANGE_DIRECTION_TIME;
	_nowDirect = direct;
}
