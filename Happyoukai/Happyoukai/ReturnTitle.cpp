#include "ReturnTitle.h"
#include "Define.h"

const Vec2 ReturnTitle::DEFAULT_POSITION = Vec2(WINDOW_WIDTH * 5 / 6, WINDOW_HEIGHT * 7 / 8);

ReturnTitle::ReturnTitle(std::shared_ptr<bool> returnTitleFlag, Vec2 position) :
	_returnTitleFlag(returnTitleFlag),
	_position(position),
	_font(WINDOW_HEIGHT / 32, L"Palatino Linotype"),
	_onMouse(false)
{
}

void ReturnTitle::update()
{
	Vec2 mousePos = Mouse::Pos();
	if (mousePos.x <= _position.x + WINDOW_WIDTH / 9
		&& mousePos.x >= _position.x - WINDOW_WIDTH / 9
		&& mousePos.y <= _position.y + WINDOW_HEIGHT / 18
		&& mousePos.y >= _position.y - WINDOW_HEIGHT / 18)
	{
		_onMouse = true;
		if (Input::MouseL.clicked) {
			*_returnTitleFlag = true;
		}
	}
	else _onMouse = false;
}

void ReturnTitle::draw() const
{
	if(_onMouse) _font(L"Return Title").drawCenter(_position.x, _position.y, HSV(120, 0.53, 0.75));
	else _font(L"Return Title").drawCenter(_position.x, _position.y, HSV(210, 0.53, 0.75));
}

void ReturnTitle::transform(int32 count)
{
	Vec2 delta = _goalPosition - _position;
	_position += delta / count;
}

void ReturnTitle::transformStart(spFieldSize fieldSize, Vec2 direct)
{
	if (direct.x == 0) {
		if (fieldSize->upLeft.x > WINDOW_WIDTH * 2 / 9)
			_goalPosition.x = fieldSize->upLeft.x / 2;
		else
			_goalPosition.x = fieldSize->downRight.x + ((WINDOW_WIDTH - fieldSize->downRight.x) / 2);
		_goalPosition.y = WINDOW_HEIGHT * 7 / 8;
	}
	else {
		if (fieldSize->upLeft.y > WINDOW_HEIGHT * 2 / 9)
			_goalPosition.y = fieldSize->upLeft.y / 2;
		else
			_goalPosition.y = fieldSize->downRight.y + ((WINDOW_HEIGHT - fieldSize->downRight.y) / 2);
		_goalPosition.x = WINDOW_WIDTH * 7 / 8;
	}
}
