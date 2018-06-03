#pragma once
#include "Define.h"
#include "Effect.h"
# include "Graph.h"
#include "RingMenu.h"
#include <memory>

class Title : public MyApp::Scene
{
public:
	// クラスの初期化時に一度だけ呼ばれる（省略可）
	void init() override;

	// 毎フレーム updateAndDraw() で呼ばれる
	void update() override;

	// 毎フレーム update() の次に呼ばれる
	void draw() const override;

private:
	std::unique_ptr<RingMenu> _ringMenu;
	GraphManager _graphManager;
	int32 fadeCount;
};