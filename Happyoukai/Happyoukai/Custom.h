#pragma once
# include "Define.h"

class Custom : public MyApp::Scene
{
public:
	void update() override
	{
		if (Input::MouseL.clicked)
			changeScene(L"Title", 2000);
	}

	void draw() const override
	{

	}
};