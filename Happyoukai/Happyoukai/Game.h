#pragma once
# include "Define.h"
# include "Graph.h"
#include "ObjectManager.h"
#include "Field.h"
#include "BackGround.h"
#include "Arrow.h"

class Game : public MyApp::Scene
{
public:
	void init() override;

	void update() override;

	void draw() const override;

private:
	void decideTravelDirection();

	spGraphManager _spObjectGraphManager;
	spGraphManager _spUIGraphManager;
	std::shared_ptr<ObjectManager> _spObjectManager;

	std::unique_ptr<BackGround> _backGround;
	std::unique_ptr<Field> _field;

	Vec2 _directionCache;
	std::shared_ptr<Vec2> _travelDirection;

	spObject _spPlayer;
	TravelArrow _arrow;
};