#pragma once
# include "Define.h"

class Game : public MyApp::Scene
{
public:
	void update() override
	{
		m_data->_effectManager.update();
		if (Input::MouseL.clicked) {
			m_data->_effectManager.fadeOut();
			changeScene(L"Result", 0);
		}
	}

	void draw() const override
	{

	}
};