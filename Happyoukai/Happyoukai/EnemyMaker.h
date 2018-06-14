#pragma once

#include "Object.h"
#include "Graph.h"
#include "AddRequestListener.h"
#include "Field.h"
#include "EnemyParam.h"

class EnemyMaker : public Object {
public:
	static const float ENEMY_SPEED;

	EnemyMaker(spGraphManager spGM, std::shared_ptr<AddRequestListner> addRequestListner, spFieldSize spFS, std::shared_ptr<int32> score, EnemyParam&& enemyParam, std::shared_ptr<Vec2> direct);

	bool update() override;
	void draw() const override;

	void collision(const spObject) override;

private:
	void calcPos();

	spGraphManager _spGraphManager;
	std::shared_ptr<AddRequestListner> _addRequestListner;
	
	std::shared_ptr<int32> _score;
	EnemyParam _enemyParam;

	std::shared_ptr<Vec2> _direct;

};