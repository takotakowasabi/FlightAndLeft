#include "Title.h"

void Title::init()
{
//	m_data->_effectManager.fadeGraph(Texture(L"images/test.png"));
}

void Title::update()
{
	m_data->_effectManager.update();
	if (Input::MouseL.clicked)
	{
		m_data->_effectManager.fadeOut();
		// 次のシーケンスと、フェードイン・アウトの時間（ミリ秒）
		changeScene(L"Game", 0);
	}
}

void Title::draw() const
{
}
