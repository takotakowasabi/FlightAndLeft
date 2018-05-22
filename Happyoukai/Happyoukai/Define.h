#pragma once
# include <Siv3D.hpp>
# include <HamFramework.hpp>
# include "Effect.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

struct GameData
{
	EffectManager _effectManager;;
};

// �V�[���̃L�[�̌^�ƁA���L�f�[�^�̌^���w��
using MyApp = SceneManager<String, GameData>;