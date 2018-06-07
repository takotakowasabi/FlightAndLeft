#include "LifeViewer.h"
#include "Define.h"

const Vec2 LifeViewer::DEFAULT_POSITION = Vec2(WINDOW_WIDTH * 5 / 6, WINDOW_HEIGHT * 3 / 8);

LifeViewer::LifeViewer(std::shared_ptr<int32> life, Vec2 position) :
	_position(position),
	_life(life),
	_lifeImage(L"images/Life.png"),
	_noLifeImage(L"images/NoLife.png")
{
}

void LifeViewer::update()
{
}

void LifeViewer::draw() const
{
	for (int i = 0; i < 3; i++) {
		if (*_life > i) _lifeImage
			.resize(WINDOW_WIDTH / 20, WINDOW_WIDTH / 20)
			.drawAt(_position.x + ((WINDOW_WIDTH / 18) * (i - 1)), _position.y);
		else _noLifeImage
			.resize(WINDOW_WIDTH / 20, WINDOW_WIDTH / 20)
			.drawAt(_position.x + ((WINDOW_WIDTH / 18) * (i - 1)), _position.y);
	}
}

void LifeViewer::transform(int32 count)
{
	Vec2 delta = _goalPosition - _position;
	_position += delta / count;
}

void LifeViewer::transformStart(spFieldSize fieldSize, Vec2 direct)
{
	if (direct.x == 0) {
		if (fieldSize->upLeft.x > WINDOW_WIDTH * 2 / 9)
			_goalPosition.x = fieldSize->upLeft.x / 2;
		else
			_goalPosition.x = fieldSize->downRight.x + ((WINDOW_WIDTH - fieldSize->downRight.x) / 2);
		_goalPosition.y = WINDOW_HEIGHT * 3 / 8;
	}
	else {
		if (fieldSize->upLeft.y > WINDOW_HEIGHT * 2 / 9)
			_goalPosition.y = fieldSize->upLeft.y / 2;
		else
			_goalPosition.y = fieldSize->downRight.y + ((WINDOW_HEIGHT - fieldSize->downRight.y) / 2);
		_goalPosition.x = WINDOW_WIDTH * 3 / 8;
	}
}