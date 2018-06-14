#pragma once
# include "Define.h"
#include "Graph.h"
#include <functional>

class Result : public MyApp::Scene
{
public:
	void init() override;

	void update() override;

	void draw() const override;

private:
	Font _font;
	String _message;
	int32 _score;

	int32 _fadeCount;
	int32 _fadeInCount;
	GraphManager _graphManager;
	Stopwatch _stopwatch;
	std::function<void(KineticTypography& k)> _animation;
};