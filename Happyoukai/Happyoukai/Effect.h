#pragma once
#include <rnfs.h>
#include <Siv3D.hpp>
#include <functional>
#include <vector>
#include <memory>

class EffectPart : public Task {
public:
	EffectPart(int32 limit, Vec2 pos, std::function<void(int32&, Vec2&, Texture&)>&& updateFunc, Texture&& tex = Texture());
private:
	Vec2 _pos;
	Texture _tex;
	std::function<void(int32&, Vec2&, Texture&)> _updateFunc;
	int32 _count;
	TaskCall _update;

	void update();
};

class EffectManager{
public:
	EffectManager() = default;
	~EffectManager();

	void fadeOut();
//	void fadeGraph(Texture&& tex);

	void update();
private:
//	TaskKeepArray<EffectPart> _effectParts;
};