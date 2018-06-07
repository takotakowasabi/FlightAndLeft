#pragma once
# include "Define.h"
# include "Graph.h"
#include "ObjectManager.h"
#include "Field.h"
#include "BackGround.h"
#include "Arrow.h"
#include "Player.h"
#include "UIManager.h"

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
	UIManager _uiManager;

	std::unique_ptr<BackGround> _backGround;
	std::unique_ptr<Field> _field;

	Vec2 _directionCache;
	std::shared_ptr<Vec2> _travelDirection;

	std::shared_ptr<Player> _spPlayer;
	TravelArrow _arrow;

	int32 _tranformCount;
	int32 _returnTitleCount;

	std::shared_ptr<int32> _score;
	std::shared_ptr<int32> _limitTime;
	std::shared_ptr<bool> _returnTitleFlag;
};