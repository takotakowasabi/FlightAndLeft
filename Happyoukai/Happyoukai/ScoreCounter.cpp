#include "ScoreCounter.h"
#include "Define.h"

const Vec2 ScoreCounter::DEFAULT_POSITION = Vec2(WINDOW_WIDTH * 5 / 6, WINDOW_HEIGHT / 8);

ScoreCounter::ScoreCounter(std::shared_ptr<int32> score, Vec2 position) :
	_position(position),
	_score(score),
	_font(WINDOW_HEIGHT / 24, L"Palatino Linotype"),
	_drawScore(0)
{
}

void ScoreCounter::update()
{
	if (*_score - _drawScore) ++_drawScore;
}

void ScoreCounter::draw() const
{
	_font(L"SCORE").drawCenter(_position.x, _position.y - WINDOW_HEIGHT / 32, HSV(210, 0.53, 0.75));
	_font(_drawScore).drawCenter(_position.x, _position.y + WINDOW_HEIGHT / 32, HSV(177, 55, 100));
}

void ScoreCounter::transform(int32 count)
{
	Vec2 delta = _goalPosition - _position;
	_position += delta / count;
}

void ScoreCounter::transformStart(spFieldSize fieldSize, Vec2 direct)
{
	if (direct.x == 0) {
		if (fieldSize->upLeft.x > WINDOW_WIDTH * 2 / 9) 
			_goalPosition.x = fieldSize->upLeft.x / 2;
		else
			_goalPosition.x = fieldSize->downRight.x + ((WINDOW_WIDTH - fieldSize->downRight.x) / 2);
		_goalPosition.y = WINDOW_HEIGHT / 8;
	}
	else {
		if (fieldSize->upLeft.y > WINDOW_HEIGHT * 2 / 9)
			_goalPosition.y = fieldSize->upLeft.y / 2;
		else
			_goalPosition.y = fieldSize->downRight.y + ((WINDOW_HEIGHT - fieldSize->downRight.y) / 2);
		_goalPosition.x = WINDOW_WIDTH / 8;
	}
}
