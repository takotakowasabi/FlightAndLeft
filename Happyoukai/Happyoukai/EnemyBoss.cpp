#include "EnemyBoss.h"
#include "Define.h"

const float EnemyBoss::DEFAULT_RADIUS = static_cast<float>(WINDOW_WIDTH) / 80.0f;
const size_t EnemyBoss::DEFAULT_LIFE_MAX = 1;

EnemyBoss::EnemyBoss(spGraphManager spGM, std::shared_ptr<AddRequestListner> addRequestListner, spFieldSize spFS, std::shared_ptr<int32> score, EnemyParam&& enemyParam, std::shared_ptr<Vec2> direct) :
	Object(enemyParam.position, enemyParam.radius, ObjectGroup::enemyCharacter, spFS),
	_direction(enemyParam.direction),
	_velocity(enemyParam.velocity),
	_texture(enemyParam.texture),
	_angle(0),
	_life(enemyParam.life),
	_spGraphManager(spGM),
	_addRequestListner(addRequestListner),
	_score(score),
	_direct(direct),
	_pressedCount(0)
{
	/*
	_imageNum = _spGraphManager->addC(
		std::move(enemyParam.texture),
		std::move(_position),
		Vec2(DEFAULT_RADIUS * 4, DEFAULT_RADIUS * 4),
		false
	);
	*/
}

bool EnemyBoss::update()
{
	if (isIntoField()) {
		move();
		shootBullet();
	}
	else {
		if (_direction != *_direct) {
			_direction = *_direct;
			rotate();
		}
		calcPos();
	}

//	_spGraphManager->changeCenter(_imageNum, _position);

//	if (_life <= 0) _spGraphManager->deleteGraph(_imageNum);
	return _life <= 0;
}

void EnemyBoss::draw() const
{
	if (isIntoField()) {
		_texture
			.resize(_radius * 2, _radius * 2)
			.rotate(Radians(_angle))
			.drawAt(_position.x, _position.y);
	}
}

void EnemyBoss::collision(const spObject)
{
	if (isIntoField()) {
		*_score += 100;
		--_life;
	}
}

bool EnemyBoss::isBossLive()
{
	return !(_life <= 0);
}

void EnemyBoss::calcPos()
{
	_position -= *_direct * 2.0f;
	if (_position.y > LOOP_FIELD_HEIGHT) _position.y = 0;
	else if (_position.y < 0) _position.y = LOOP_FIELD_HEIGHT;
	if (_position.x > LOOP_FIELD_WIDTH) _position.x = 0;
	else if (_position.x < 0) _position.x = LOOP_FIELD_WIDTH;
}

void EnemyBoss::move()
{
	_position += -_direction * 2.f;
}

void EnemyBoss::rotate()
{
	int32 direction = 0;
	if (abs(_direction.y - 1) < 0.1) direction = 180;
	else if (abs(_direction.x + 1) < 0.1) direction = -90;
	else if (abs(_direction.x - 1) < 0.1) direction = 90;

	_angle = direction;
}

void EnemyBoss::shootBullet()
{
	_pressedCount++;
	const int32 SHOOT_POSITION = _radius / 2;
	const float BULLET_RADIUS = WINDOW_HEIGHT / 240.f;
	const float BIG_BULLET_RADIUS = WINDOW_HEIGHT / 40.f;
	const Color BULLET_COLOR = Color(216, 216, 216);

	if (_pressedCount % 30 == 29) {
		if (_direction.x == 0) {
			_addRequestListner->addObject(std::make_shared<Bullet>(
				_position + Vec2(SHOOT_POSITION, 0),
				ObjectGroup::enemyObject,
				_spFieldSize,
				BULLET_RADIUS,
				(-_direction * 10.0),
				BULLET_COLOR
				));
			_addRequestListner->addObject(std::make_shared<Bullet>(
				_position - Vec2(SHOOT_POSITION, 0),
				ObjectGroup::enemyObject,
				_spFieldSize,
				BULLET_RADIUS,
				(-_direction * 10.0),
				BULLET_COLOR
				));
		}
		else {
			_addRequestListner->addObject(std::make_shared<Bullet>(
				_position + Vec2(0, SHOOT_POSITION),
				ObjectGroup::enemyObject,
				_spFieldSize,
				BULLET_RADIUS,
				(-_direction * 10.0),
				BULLET_COLOR
				));
			_addRequestListner->addObject(std::make_shared<Bullet>(
				_position - Vec2(0, SHOOT_POSITION),
				ObjectGroup::enemyObject,
				_spFieldSize,
				BULLET_RADIUS,
				(-_direction * 10.0),
				BULLET_COLOR
				));
		}
	}
	if (_pressedCount % 120 == 119) {
		if (_direction.x == 0) {
			_addRequestListner->addObject(std::make_shared<Bullet>(
				_position,
				ObjectGroup::enemyObject,
				_spFieldSize,
				BIG_BULLET_RADIUS,
				(-_direction * 10.0),
				BULLET_COLOR
				));
		}
		else {
			_addRequestListner->addObject(std::make_shared<Bullet>(
				_position,
				ObjectGroup::enemyObject,
				_spFieldSize,
				BIG_BULLET_RADIUS,
				(-_direction * 10.0),
				BULLET_COLOR
				));
		}
	}
}

bool EnemyBoss::isIntoField() const
{
	if (_position.x + _radius * 2 < _spFieldSize->upLeft.x) return false;
	if (_position.x - _radius * 2 > _spFieldSize->downRight.x) return false;
	if (_position.y + _radius * 2 < _spFieldSize->upLeft.y) return false;
	if (_position.y - _radius * 2 > _spFieldSize->downRight.y) return false;
	return true;
}
