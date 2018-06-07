#include "Enemy.h"
#include "Define.h"

const float Enemy::DEFAULT_RADIUS = static_cast<float>(WINDOW_WIDTH) / 80.0f;
const size_t Enemy::DEFAULT_LIFE_MAX = 1;

Enemy::Enemy(spGraphManager spGM, std::shared_ptr<AddRequestListner> addRequestListner, spFieldSize spFS, std::shared_ptr<int32> score, EnemyParam&& enemyParam) :
	Object(enemyParam.position, enemyParam.radius, ObjectGroup::enemyCharacter, spFS),
	_velocity(enemyParam.velocity),
	_life(enemyParam.life),
	_spGraphManager(spGM),
	_addRequestListner(addRequestListner),
	_score(score)
{
	_imageNum = _spGraphManager->addC(
		Texture(L"images/Enemy.png"),
		std::move(_position),
		Vec2(DEFAULT_RADIUS * 4, DEFAULT_RADIUS * 4),
		false
	);
}

bool Enemy::update()
{
	move();
	shootBullet();

	if (_life <= 0 || !isInField()) _spGraphManager->deleteGraph(_imageNum);
	return !isInField() || (_life <= 0);
}

void Enemy::draw() const
{
}

void Enemy::collision(const spObject)
{
	*_score += 100;
	--_life;
}

void Enemy::move()
{
	_position += _velocity;
	_spGraphManager->changeCenter(_imageNum, _position);
}

void Enemy::shootBullet()
{
}
