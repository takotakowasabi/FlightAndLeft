#include "EnemyMaker.h"

const float EnemyMaker::ENEMY_SPEED = 2.0f;

EnemyMaker::EnemyMaker(spGraphManager spGM, std::shared_ptr<AddRequestListner> addRequestListner, spFieldSize spFS, std::shared_ptr<int32> score, EnemyParam && enemyParam, std::shared_ptr<Vec2> direct) :
	Object(enemyParam.position, -enemyParam.radius, ObjectGroup::enemyCharacter, spFS),
	_spGraphManager(spGM),
	_addRequestListner(addRequestListner),
	_score(score),
	_enemyParam(enemyParam),
	_direct(direct)
{
}

bool EnemyMaker::update()
{
	if (isInField()) {
		float dirAngle = 0.0f;
		if (_direct->x == 1) dirAngle = Pi;
		if (_direct->y == -1) dirAngle = Pi / 2;
		if (_direct->y == 1) dirAngle = -Pi / 2;
		_enemyParam.velocity.rotate(dirAngle);
		_addRequestListner->addObject(std::make_shared<Enemy>(
			_spGraphManager,
			_addRequestListner,
			_spFieldSize,
			_score,
			EnemyParam(_enemyParam.texture, _position, _enemyParam.velocity, *_direct, _enemyParam.life, _enemyParam.radius)
			));
		return true;
	}
	calcPos();
	return false;
}

void EnemyMaker::draw() const
{
}

void EnemyMaker::collision(const spObject)
{
}

void EnemyMaker::calcPos()
{
	_position -= *_direct * ENEMY_SPEED;
	if (_position.y > LOOP_FIELD_HEIGHT) _position.y = 0;
	else if (_position.y < 0) _position.y = LOOP_FIELD_HEIGHT;
	if (_position.x > LOOP_FIELD_WIDTH) _position.x = 0;
	else if (_position.x < 0) _position.x = LOOP_FIELD_WIDTH;
}