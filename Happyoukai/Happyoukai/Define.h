#pragma once
# include <Siv3D.hpp>
# include <HamFramework.hpp>
# include "Effect.h"

const int32 WINDOW_WIDTH = 640;
const int32 WINDOW_HEIGHT = 480;

const int32 CHANGE_DIRECTION_TIME = 60;

struct GameData
{
	EffectManager _effectManager;
};

/*
float vec2toAngle(const Vec2& vec) {
	return Atan(vec.y / vec.x);
}
*/

// シーンのキーの型と、共有データの型を指定
using MyApp = SceneManager<String, GameData>;