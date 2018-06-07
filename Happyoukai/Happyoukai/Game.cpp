#include "Game.h"
#include "Player.h"
#include "Enemy.h"

void Game::init()
{
	_spObjectGraphManager = std::make_shared<GraphManager>();
	_spUIGraphManager = std::make_shared<GraphManager>();
	_spObjectManager = std::make_shared<ObjectManager>();
	_backGround = std::make_unique<BackGround>();
	_field = std::make_unique<Field>();
	_travelDirection = std::make_shared<Vec2>(0.0, -1.0);
	_directionCache = *_travelDirection;

	_spPlayer = _spObjectManager->addObject(std::make_shared<Player>(_spObjectGraphManager, _spObjectManager, _field->getSize()));
	
	//debug
	Vec2 enemyPos = Vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4);
	Vec2 enemyVel = Vec2(0, 0);
	_spObjectManager->addObject(std::make_shared<Enemy>(
		_spObjectGraphManager, _spObjectManager, _field->getSize(), EnemyParam(enemyPos, enemyVel)));
	//

	Image fadeIn(WINDOW_WIDTH, WINDOW_HEIGHT, Color(248));
	size_t fadeInNum = _spUIGraphManager->add(
		Texture(fadeIn),
		Vec2(0, 0),
		Vec2(WINDOW_WIDTH, WINDOW_HEIGHT),
		false
	);
	_spUIGraphManager->fadeOut(fadeInNum);
}

void Game::update()
{
	if (!Input::MouseR.pressed) {
		if (_directionCache != *_travelDirection) {
			_field->transform(_spPlayer->getPosition(), *_travelDirection);
			_directionCache = *_travelDirection;
		}
		else {
			_spObjectManager->update();
		}
	}
	else {
		decideTravelDirection();
	}
	
	_field->update();
	_spObjectGraphManager->update();
	_spUIGraphManager->update();
	m_data->_effectManager.update();

/*	if (Input::MouseL.clicked) {
		changeScene(L"Result", 100);
	}*/
}

void Game::draw() const
{
	_field->draw();
	_backGround->drawBackGround();
	_spObjectManager->draw();
	_spObjectGraphManager->draw();
	_backGround->drawUIBase();
	_spUIGraphManager->draw();
	if (Input::MouseR.pressed) {
		_arrow.draw(*_travelDirection, _spPlayer->getPosition());
	}
}

void Game::decideTravelDirection()
{
	Vec2 mousePos = Mouse::Pos();
	Vec2 ret = mousePos - _spPlayer->getPosition();
	double dirDif = abs(ret.x) - abs(ret.y);
	if (dirDif > 0.0) ret.y = 0;
	else if (dirDif <= 0.0) ret.x = 0;
	ret.normalize();
	*_travelDirection = ret;
}
