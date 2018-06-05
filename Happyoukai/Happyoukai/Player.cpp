#include "Player.h"
#include "Define.h"

const float Player::DEFAULT_RADIUS = static_cast<float>(WINDOW_WIDTH) / 160.0f;
const float Player::DEFAULT_DELAY = 0.4f;
const size_t Player::LIFE_MAX = 3;
const float Player::MAX_SPEED = static_cast<float>(WINDOW_WIDTH) / 40.0f;

Player::Player(spGraphManager spGM, std::shared_ptr<AddRequestListner> addRequestListner) :
	Object(Vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 3 / 4), DEFAULT_RADIUS, ObjectGroup::friendCharacter),
	_moveDelay(DEFAULT_DELAY),
	_life(LIFE_MAX),
	_spGraphManager(spGM),
	_addRequestListner(addRequestListner)
{
	_imageNum = _spGraphManager->addC(
		Texture(L"images/Player.png"),
		std::move(_position),
		Vec2(DEFAULT_RADIUS * 8, DEFAULT_RADIUS * 8),
		false
	);
}

bool Player::update()
{
//	Println(DEFAULT_RADIUS);

	move();
	shootBullet();
	_spGraphManager->changeCenter(_imageNum, _position);

	return false;
}

void Player::draw() const
{
}

void Player::collision(const spObject)
{
}

void Player::move()
{
	Vec2 deltaPos = (Mouse::Pos() - _position) * _moveDelay;

	if (deltaPos.length() > MAX_SPEED) {
		deltaPos /= deltaPos.length();
		deltaPos *= MAX_SPEED;
	}

	_position += deltaPos;
}

void Player::shootBullet()
{
	if (Input::MouseL.pressedDuration % 5 == 1) {
		_addRequestListner->addObject(std::make_shared<Bullet>(
			_position,
			ObjectGroup::friendObject
			));
	}
}
