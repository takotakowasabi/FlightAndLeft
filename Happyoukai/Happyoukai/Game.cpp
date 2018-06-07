#include "Game.h"
#include "Enemy.h"
#include "Define.h"
#include "ScoreCounter.h"
#include "LifeViewer.h"
#include "LimitTimer.h"
#include "ReturnTitle.h"

void Game::init()
{
	_spObjectGraphManager = std::make_shared<GraphManager>();
	_spUIGraphManager = std::make_shared<GraphManager>();
	_spObjectManager = std::make_shared<ObjectManager>();
	_backGround = std::make_unique<BackGround>();
	_field = std::make_unique<Field>();
	_travelDirection = std::make_shared<Vec2>(0.0, -1.0);
	_directionCache = *_travelDirection;
	_tranformCount = 0;
	_score = std::make_shared<int32>(0);
	_limitTime = std::make_shared<int32>(10800);
	_returnTitleFlag = std::make_shared<bool>(false);

	_spPlayer = std::make_shared<Player>(_spObjectGraphManager, _spObjectManager, _field->getSize());
	_spObjectManager->addObject(_spPlayer);

	_uiManager.addUI(std::make_shared<ScoreCounter>(_score));
	_uiManager.addUI(std::make_shared<LifeViewer>(_spPlayer->getLife()));
	_uiManager.addUI(std::make_shared<LimitTimer>(_limitTime));
	_uiManager.addUI(std::make_shared<ReturnTitle>(_returnTitleFlag));
	
	//debug
	Vec2 enemyPos = Vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4);
	Vec2 enemyVel = Vec2(0, 0);
	_spObjectManager->addObject(std::make_shared<Enemy>(
		_spObjectGraphManager, _spObjectManager, _field->getSize(), _score, EnemyParam(enemyPos, enemyVel)));
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
	if (*_returnTitleFlag) {
		if (_returnTitleCount == 85) changeScene(L"Title", 100);
		else if (_returnTitleCount) ++_returnTitleCount;
		else {
			Image fadeIn(WINDOW_WIDTH, WINDOW_HEIGHT, Color(248));
			_spUIGraphManager->add(
				Texture(fadeIn),
				Vec2(0, 0),
				Vec2(WINDOW_WIDTH, WINDOW_HEIGHT),
				true
			);
			++_returnTitleCount;
		}
	}
	else if (!Input::MouseR.pressed) {
		if (_directionCache != *_travelDirection) {
			_field->transform(_spPlayer->getPosition(), *_travelDirection);
			_directionCache = *_travelDirection;
			_spPlayer->rotateStart(*_travelDirection);
			_tranformCount = CHANGE_DIRECTION_TIME;
			_uiManager.transformStart(_field->getGoalSize(), *_travelDirection);
		}
		if (_tranformCount) {
			_spPlayer->rotate(_tranformCount);
			_uiManager.transform(_tranformCount);
			--_tranformCount;
		}
		else {
			_spObjectManager->update();
			_uiManager.update();
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
	_uiManager.draw();
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
