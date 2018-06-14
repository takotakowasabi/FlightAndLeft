#include "Result.h"
#include "Define.h"

void Result::init()
{
	_fadeCount = 0;
	_fadeCount = 0;
	_stopwatch = Stopwatch(false);

	Image fadeIn(WINDOW_WIDTH, WINDOW_HEIGHT, Color(248));
	size_t fadeInNum = _graphManager.add(
		Texture(fadeIn),
		Vec2(0, 0),
		Vec2(WINDOW_WIDTH, WINDOW_HEIGHT),
		false
	);
	_graphManager.fadeOut(fadeInNum);

	_font = Font(WINDOW_HEIGHT / 24, L"Palatino Linotype");
	if (m_data->_score > 0) _message = L"Congratulations !";
	else _message = L"Game Over";
	_score = abs(m_data->_score);
}

void Result::update()
{
	++_fadeInCount;
	_graphManager.update();
	if (_fadeInCount == 85) {
		_stopwatch.start();
	}
	if(_fadeCount == 85) changeScene(L"Title", 100);
	else if (_fadeCount) ++_fadeCount;
	else {
		m_data->_effectManager.update();
		/*
		const double index = _stopwatch.ms() / 80.0;
		_animation = [=](KineticTypography& k)
		{
			const double t = index - k.index;

			k.col.a = AlphaF(Saturate(t / 6)).toColor().a;

			k.pos.y -= EaseIn<Easing::Quad>(Saturate(1 - t / 4)) * 20.0;
		};
		*/
		if (Input::MouseL.clicked) {
			Image fadeIn(WINDOW_WIDTH, WINDOW_HEIGHT, Color(248));
			_graphManager.add(
				Texture(fadeIn),
				Vec2(0, 0),
				Vec2(WINDOW_WIDTH, WINDOW_HEIGHT),
				true
			);
			++_fadeCount;
		}
	}
}

void Result::draw() const
{
	const double index = _stopwatch.ms() / 80.0;
	const auto animation = [=](KineticTypography& k)
	{
		const double t = index - k.index;

		k.col.a = AlphaF(Saturate(t / 6)).toColor().a;

		k.pos.y -= EaseIn<Easing::Quad>(Saturate(1 - t / 4)) * 20.0;
	};

	_font(_message).drawKinetic(WINDOW_WIDTH / 6, WINDOW_HEIGHT / 6, animation, HSV(210, 0.53, 0.75));
	_font(L"Score : ", _score).drawKinetic(WINDOW_WIDTH / 6, WINDOW_HEIGHT * 2 / 3, animation, HSV(210, 0.53, 0.75));

	_graphManager.draw();
}
