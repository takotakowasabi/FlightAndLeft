#include "Game.h"

void Game::init()
{
	_spGraphManager = std::make_shared<GraphManager>();
	_spObjectManager = std::make_shared<ObjectManager>();

	_spObjectManager->addObject(std::make_shared<Player>(_spGraphManager, _spObjectManager));
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
	_spGraphManager->draw();
	_spObjectManager->draw();
}
