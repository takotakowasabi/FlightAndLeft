#include "Player.h"
#include "Define.h"

const float Player::DEFAULT_RADIUS = static_cast<float>(WINDOW_WIDTH) / 80.0f;
const float Player::DEFAULT_DELAY = 0.4f;
const size_t Player::LIFE_MAX = 3;
const float Player::MAX_SPEED = static_cast<float>(WINDOW_WIDTH) / 40.0f;
const float Player::SHOOT_POSITION = static_cast<float>(WINDOW_WIDTH) / 80.0f;

Player::Player(spGraphManager spGM, std::shared_ptr<AddRequestListner> addRequestListner, spFieldSize spFS) :
	Object(Vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 3 / 4), DEFAULT_RADIUS, ObjectGroup::friendCharacter, spFS),
	_moveDelay(DEFAULT_DELAY),
	_life(std::make_shared<int32>(LIFE_MAX)),
	_presseedCount(0),
	_spGraphManager(spGM),
	_addRequestListner(addRequestListner),
	_dirVec(0.0, -1.0),
	_direction(0.0f),
	_goalDirection(0.0f)
{
	_imageNum = _spGraphManager->addC(
		Texture(L"images/Player.png"),
		std::move(_position),
		Vec2(DEFAULT_RADIUS * 4, DEFAULT_RADIUS * 4),
		false
	);
}

bool Player::update()
{
//	Println(DEFAULT_RADIUS);

	move();
	shootBullet();

	return false;
}

void Player::draw() const
{
}

void Player::collision(const spObject)
{
	--*_life;
}

void Player::rotate(int32 count)
{
	if (_direction == _goalDirection) return;
	float delta = _goalDirection - _direction;
	_direction += delta / count;
	_spGraphManager->rotateAt(_imageNum, static_cast<int32>(_direction));
}

void Player::rotateStart(const Vec2 & goalVec)
{
	_dirVec = goalVec;
	if (goalVec.x == 1) {
		_goalDirection = 90.0f;
	}
	else if (goalVec.x == -1) {
		_goalDirection = -90.0f;
	}
	else if (goalVec.y == 1) {
		_goalDirection = 180.0f;
	}
	else if (goalVec.y == -1) {
		_goalDirection = 0.0f;
	}
}

const std::shared_ptr<int32> Player::getLife()
{
	return _life;
}

void Player::move()
{
	Vec2 deltaPos = (Mouse::Pos() - _position) * _moveDelay;

	if (deltaPos.length() > MAX_SPEED) {
		deltaPos /= deltaPos.length();
		deltaPos *= MAX_SPEED;
	}

	_position += deltaPos;

	if (!isInFieldX()) _position.x -= deltaPos.x;
	if (!isInFieldY()) _position.y -= deltaPos.y;

	_spGraphManager->changeCenter(_imageNum, _position);
}

void Player::shootBullet()
{
	if (Input::MouseL.pressed) {
		_presseedCount++;
		if (_presseedCount % 5 == 1) {
			if (_dirVec.x == 0) {
				_addRequestListner->addObject(std::make_shared<Bullet>(
					_position + Vec2(SHOOT_POSITION, 0),
					ObjectGroup::friendObject,
					_spFieldSize,
					2.0,
					(_dirVec * 10.0)
					));
				_addRequestListner->addObject(std::make_shared<Bullet>(
					_position - Vec2(SHOOT_POSITION, 0),
					ObjectGroup::friendObject,
					_spFieldSize,
					2.0,
					(_dirVec * 10.0)
					));
			}
			else {
				_addRequestListner->addObject(std::make_shared<Bullet>(
					_position + Vec2(0, SHOOT_POSITION),
					ObjectGroup::friendObject,
					_spFieldSize,
					2.0,
					(_dirVec * 10.0)
					));
				_addRequestListner->addObject(std::make_shared<Bullet>(
					_position - Vec2(0, SHOOT_POSITION),
					ObjectGroup::friendObject,
					_spFieldSize,
					2.0,
					(_dirVec * 10.0)
					));
			}
		}
	}
	else _presseedCount = 0;
}
