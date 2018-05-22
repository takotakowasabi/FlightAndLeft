#include "Game.h"
#include "Result.h"
#include "Title.h"
#include "Custom.h"
#include "Effect.h"

void Main()
{
	Window::Resize(WINDOW_WIDTH, WINDOW_HEIGHT);

	MyApp manager(SceneManagerOption::ShowSceneName);

	//SceneManagerOption::ShowSceneName を外せばシーン名のデバッグ表示は消える
	//MyApp manager;

	// フェードイン・アウト時の色

	// シーンを設定
	manager.add<Title>(L"Title");
	manager.add<Game>(L"Game");
	manager.add<Result>(L"Result");
	manager.add<Custom>(L"Coustom");

	// 特に指定しなければ、一番最初に追加したシーンから開始
	// 別のシーンから始めたい場合は init()
	manager.init(L"Title");

	while (System::Update())
	{
		ClearPrint();
		if (!manager.updateAndDraw())
			break;
	}
}