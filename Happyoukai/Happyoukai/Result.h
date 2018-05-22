#pragma once
# include "Define.h"

class Result : public MyApp::Scene
{
public:
	void update() override
	{
		m_data->_effectManager.update();
		if (Input::MouseL.clicked) {
			changeScene(L"Title", 0);
			m_data->_effectManager.fadeOut();
		}
	}

	void draw() const override
	{

	}
};