#include "Game.h"

void Game::init()
{
	_spGraphManager = std::make_shared<GraphManager>();
	_spObjectManager = std::make_shared<ObjectManager>();

	_spObjectManager->addObject(std::make_shared<Player>(_spGraphManager, _spObjectManager));

	Image fadeIn(WINDOW_WIDTH, WINDOW_HEIGHT, Color(248));
	size_t fadeInNum = _spGraphManager->add(
		Texture(fadeIn),
		Vec2(0, 0),
		Vec2(WINDOW_WIDTH, WINDOW_HEIGHT),
		false
	);
	_spGraphManager->fadeOut(fadeInNum);
}

void Game::update()
{
	_spObjectManager->update();
	_spGraphManager->update();
	m_data->_effectManager.update();

/*	if (Input::MouseL.clicked) {
		changeScene(L"Result", 100);
	}*/
}

void Game::draw() const
{
	_spObjectManager->draw();
	_spGraphManager->draw();
}
