#include "Enemy.h"
#include "Define.h"

const float Enemy::DEFAULT_RADIUS = static_cast<float>(WINDOW_WIDTH) / 80.0f;
const size_t Enemy::DEFAULT_LIFE_MAX = 1;

Enemy::Enemy(spGraphManager spGM, std::shared_ptr<AddRequestListner> addRequestListner, spFieldSize spFS, std::shared_ptr<int32> score, EnemyParam&& enemyParam) :
	Object(enemyParam.position, enemyParam.radius, ObjectGroup::enemyCharacter, spFS),
	_direction(enemyParam.direction),
	_velocity(enemyParam.velocity),
	_life(enemyParam.life),
	_spGraphManager(spGM),
	_addRequestListner(addRequestListner),
	_score(score),
	_pressedCount(0)
{
	_imageNum = _spGraphManager->addC(
		std::move(enemyParam.texture),
		std::move(_position),
		Vec2(DEFAULT_RADIUS * 4, DEFAULT_RADIUS * 4),
		false
	);
	
	int32 direction = 0;
	if (abs(_direction.y - 1) < 0.1) direction = 180;
	else if (abs(_direction.x + 1) < 0.1) direction = -90;
	else if (abs(_direction.x - 1) < 0.1) direction = 90;

	_spGraphManager->rotateAt(_imageNum, direction);
	
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
	_pressedCount++;
	const int32 SHOOT_POSITION = static_cast<float>(WINDOW_WIDTH) / 80.0f;
	const float BULLET_RADIUS = WINDOW_HEIGHT / 240.f;
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
}
