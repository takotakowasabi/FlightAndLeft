#pragma once
# include "Define.h"
# include "Graph.h"
#include "Player.h"
#include "ObjectManager.h"

class Game : public MyApp::Scene
{
public:
	void init() override;

	void update() override;

	void draw() const override;

private:
	spGraphManager _spGraphManager;
	std::shared_ptr<ObjectManager> _spObjectManager;
};