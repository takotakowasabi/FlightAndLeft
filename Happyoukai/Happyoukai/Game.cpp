#include "Game.h"
#include "EnemyMaker.h"
#include "Define.h"
#include "ScoreCounter.h"
#include "LifeViewer.h"
#include "LimitTimer.h"
#include "ReturnTitle.h"
#include "Cloud.h"

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

	const int32 CLOUD_SIZE = 100;
	for (int32 i = 0; i < CLOUD_SIZE; i++) {
		_spObjectManager->addObject(std::make_shared<Cloud>(Vec2(Random(0, LOOP_FIELD_WIDTH), Random(0, LOOP_FIELD_HEIGHT)), _field->getSize(), _travelDirection));
	}

	_spPlayer = std::make_shared<Player>(_spObjectGraphManager, _spObjectManager, _field->getSize());
	_spObjectManager->addObject(_spPlayer);

	Texture bossText = Texture(L"images/Boss.png");
	_spBoss = std::make_shared<EnemyBoss>(
		_spObjectGraphManager, _spObjectManager, _field->getSize(), _score,
		EnemyParam(
			bossText,
			//Vec2(Random(0, LOOP_FIELD_WIDTH), Random(WINDOW_HEIGHT, LOOP_FIELD_HEIGHT)),
			Vec2(200, 1000),
			Vec2(Random(0.0, 2.0), Random(-2.0, 2.0)),
			*_travelDirection,
			200U,
			WINDOW_HEIGHT / 6
		),
		_travelDirection
		);
	_spObjectManager->addObject(_spBoss);

	_uiManager.addUI(std::make_shared<ScoreCounter>(_score));
	_uiManager.addUI(std::make_shared<LifeViewer>(_spPlayer->getLife()));
	_uiManager.addUI(std::make_shared<LimitTimer>(_limitTime));
	_uiManager.addUI(std::make_shared<ReturnTitle>(_returnTitleFlag));
	
	const int32 ENEMY_SIZE = 60;
	Texture text = Texture(L"images/Enemy.png");
	for (int i = 0; i < ENEMY_SIZE; i++) {
		_spObjectManager->addObject(std::make_shared<EnemyMaker>(
			_spObjectGraphManager, _spObjectManager, _field->getSize(), _score,
			EnemyParam(
				text,
				Vec2(Random(0, LOOP_FIELD_WIDTH), Random(WINDOW_HEIGHT, LOOP_FIELD_HEIGHT)),
				Vec2(Random(0.0, 2.0), Random(-2.0, 2.0))
			),
			_travelDirection));
	}

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

	if (_goResultCount) {
		if(_goResultCount == 85) changeScene(L"Result", 100);
		++_goResultCount;
	}
	else if (*_spPlayer->getLife() <= 0 ||  _limitTime <= 0) {
		m_data->_score = -*_score;
		Image fadeIn(WINDOW_WIDTH, WINDOW_HEIGHT, Color(248));
		_spUIGraphManager->add(
			Texture(fadeIn),
			Vec2(0, 0),
			Vec2(WINDOW_WIDTH, WINDOW_HEIGHT),
			true
		);
		++_goResultCount;
	}
	else if (!_spBoss->isBossLive()) {
		m_data->_score = *_score;
		Image fadeIn(WINDOW_WIDTH, WINDOW_HEIGHT, Color(248));
		_spUIGraphManager->add(
			Texture(fadeIn),
			Vec2(0, 0),
			Vec2(WINDOW_WIDTH, WINDOW_HEIGHT),
			true
		);
		++_goResultCount;
	}
	else if (*_returnTitleFlag) {
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
			//if (_directionCache.x != _travelDirection->x && _directionCache.y != _travelDirection->y) {
			_uiManager.transformStart(_field->getGoalSize(), *_travelDirection);
			_tranformCount = CHANGE_DIRECTION_TIME;
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
