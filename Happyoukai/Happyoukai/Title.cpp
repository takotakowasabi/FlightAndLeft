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
		// ���̃V�[�P���X�ƁA�t�F�[�h�C���E�A�E�g�̎��ԁi�~���b�j
		changeScene(L"Game", 0);
	}
}

void Title::draw() const
{
}
