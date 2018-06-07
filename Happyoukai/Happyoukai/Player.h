#pragma once
#include "Object.h"
#include "Graph.h"
#include "Bullet.h"
#include "AddRequestListener.h"
#include "Field.h"

class Player : public Object{
public:
	static const float DEFAULT_RADIUS;
	static const float DEFAULT_DELAY;
	static const size_t LIFE_MAX;
	static const float MAX_SPEED;
	static const float SHOOT_POSITION;

	Player(spGraphManager spGM, std::shared_ptr<AddRequestListner> addRequestListner, spFieldSize spFS);

	bool update() override;
	void draw() const override;

	void collision(const spObject) override;
	
	void rotate(int32 count);
	void rotateStart(const Vec2& goalVec);

	const std::shared_ptr<int32> getLife();

private:
	float _moveDelay;

	void move();
	void shootBullet();

	std::shared_ptr<int32> _life;
	size_t _imageNum;

	int32 _presseedCount;

	spGraphManager _spGraphManager;
	std::shared_ptr<AddRequestListner> _addRequestListner;

	Vec2 _dirVec;
	float _direction;
	float _goalDirection;
};