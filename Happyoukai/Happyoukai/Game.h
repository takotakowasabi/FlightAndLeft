#pragma once
# include "Define.h"

class Game : public MyApp::Scene
{
public:
	void update() override
	{
		m_data->_effectManager.update();
		if (Input::MouseL.clicked) {
			changeScene(L"Result", 100);
		}
	}

	void draw() const override
	{

	}
};