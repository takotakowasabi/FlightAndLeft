#pragma once
#include "Object.h"
#include "Graph.h"
#include "Bullet.h"
#include "AddRequestListener.h"
#include "Field.h"
#include "EnemyParam.h"

class EnemyParam;

class EnemyBoss : public Object {
public:
	static const float DEFAULT_RADIUS;
	static const size_t DEFAULT_LIFE_MAX;

	EnemyBoss(spGraphManager spGM, std::shared_ptr<AddRequestListner> addRequestListner, spFieldSize spFS, std::shared_ptr<int32> score, EnemyParam&& enemyParam, std::shared_ptr<Vec2> direct);

	bool update() override;
	void draw() const override;

	void collision(const spObject) override;

	bool isBossLive();

private:
	void calcPos();
	void move();
	void rotate();
	void shootBullet();

	bool isIntoField() const;

	std::shared_ptr<Vec2> _direct;
	Vec2 _direction;
	Vec2 _velocity;
	Texture _texture;
	int32 _angle;

	int32 _life;
	int32 _pressedCount;
	size_t _imageNum;

	spGraphManager _spGraphManager;
	std::shared_ptr<AddRequestListner> _addRequestListner;
	std::shared_ptr<int32> _score;

};