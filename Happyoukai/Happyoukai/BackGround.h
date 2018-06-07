#pragma once
#include "Graph.h"

class BackGround {
public:
	BackGround();

	void update();
	void drawBackGround() const;
	void drawUIBase() const;

private:
	spGraphManager _spGraphManager;
	Texture _backGround;
	Texture _uiBase;

};