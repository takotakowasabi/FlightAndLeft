#pragma once
# include <Siv3D.hpp>
# include <HamFramework.hpp>
# include "Effect.h"

const int32 WINDOW_WIDTH = 960;
const int32 WINDOW_HEIGHT = 720;

const int32 LOOP_FIELD_WIDTH = 4800;
const int32 LOOP_FIELD_HEIGHT = 3600;

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

// �V�[���̃L�[�̌^�ƁA���L�f�[�^�̌^���w��
using MyApp = SceneManager<String, GameData>;