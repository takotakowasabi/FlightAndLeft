#pragma once
# include <Siv3D.hpp>
# include <HamFramework.hpp>
# include "Effect.h"

const int32 WINDOW_WIDTH = 960;
const int32 WINDOW_HEIGHT = 720;

const int32 LOOP_FIELD_WIDTH = 2880;
const int32 LOOP_FIELD_HEIGHT = 2160;

const int32 CHANGE_DIRECTION_TIME = 60;

struct GameData
{
	EffectManager _effectManager;
	int32 _score;
};

/*
float vec2toAngle(const Vec2& vec) {
	return Atan(vec.y / vec.x);
}
*/

// シーンのキーの型と、共有データの型を指定
using MyApp = SceneManager<String, GameData>;