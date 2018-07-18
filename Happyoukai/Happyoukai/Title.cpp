#include "Title.h"

void Title::init()
{
	fadeCount = 0;
//	m_data->_effectManager.fadeGraph(Texture(L"images/test.png"));
	_graphManager.add(
		Texture(L"images/title.png"),
		Vec2(WINDOW_WIDTH / 54, 0),
		Vec2(WINDOW_WIDTH, WINDOW_HEIGHT * 2 / 3),
		false
	);

	Image fadeIn(WINDOW_WIDTH, WINDOW_HEIGHT, Color(248));
	size_t fadeInNum = _graphManager.add(
		Texture(fadeIn),
		Vec2(0, 0),
		Vec2(WINDOW_WIDTH, WINDOW_HEIGHT),
		false
	);
	_graphManager.fadeOut(fadeInNum);

	_ringMenu = std::make_unique<RingMenu>(Vec2(WINDOW_WIDTH / 4, WINDOW_HEIGHT * 4 / 7), Vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 3 / 7));
	_ringMenu->addPart(L"start");
//	_ringMenu->addPart(L"config");
//	_ringMenu->addPart(L"credit");
	_ringMenu->addPart(L"exit");
}

void Title::update()
{
	_graphManager.update();

	if (_ringMenu->update() && !fadeCount)
	{
		if (_ringMenu->pressedPart() == 0) {
			Image fadeIn(WINDOW_WIDTH, WINDOW_HEIGHT, Color(248));
			_graphManager.add(
				Texture(fadeIn),
				Vec2(0, 0),
				Vec2(WINDOW_WIDTH, WINDOW_HEIGHT),
				true
			);
			++fadeCount;
		}
		if (_ringMenu->pressedPart() == 3) {
			System::Exit();
		}
	}
	else if (fadeCount == 85) changeScene(L"Game", 100);
	else if (fadeCount) fadeCount++;
}

void Title::draw() const
{
	_ringMenu->draw();
	m_data->_effectManager.update();
	_graphManager.draw();
}
