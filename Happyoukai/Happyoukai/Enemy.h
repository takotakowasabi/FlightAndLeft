#pragma once
#include "Object.h"
#include "Graph.h"
#include "Bullet.h"
#include "AddRequestListener.h"
#include "Field.h"
#include "EnemyParam.h"

class Enemy : public Object {
public:
	static const float DEFAULT_RADIUS;
	static const size_t DEFAULT_LIFE_MAX;

	Enemy(spGraphManager spGM, std::shared_ptr<AddRequestListner> addRequestListner, spFieldSize spFS, std::shared_ptr<int32> score, EnemyParam&& enemyParam);

	bool update() override;
	void draw() const override;

	void collision(const spObject) override;

private:
	void move();
	void shootBullet();

	Vec2 _velocity;

	int32 _life;
	size_t _imageNum;

	spGraphManager _spGraphManager;
	std::shared_ptr<AddRequestListner> _addRequestListner;
	std::shared_ptr<int32> _score;

};