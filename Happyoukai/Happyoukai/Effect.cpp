#include "Effect.h"
#include "Define.h"
#include <Siv3D.hpp>

EffectPart::EffectPart(int32 limit, Vec2 pos, std::function<void(int32&, Vec2&, Texture&)>&& updateFunc, Texture&& tex) :
	Task(limit),
	_pos(pos),
	_tex(tex),
	_updateFunc(std::forward<std::function<void(int32&, Vec2&, Texture&)>>(updateFunc)),
	_count(0),
	_update(this, &EffectPart::update)
{
}

void EffectPart::update()
{
	Println(L"10");
	_updateFunc(_count, _pos, _tex);
	/*
	if (_count < 0) {
		this->Destroy();
	}
	*/
}

EffectManager::~EffectManager()
{
	//_effectParts.Clear_All();
	Task::All::Clear();
}

void EffectManager::fadeOut()
{
	Create<EffectPart>(180, Vec2(-WINDOW_WIDTH, -WINDOW_HEIGHT), [](int32& count, Vec2& pos, Texture& tex) {
		Line(pos.x, -WINDOW_WIDTH*2, -WINDOW_HEIGHT*2, pos.y).draw(WINDOW_WIDTH);
		Line(pos.x * 1 / 2, -WINDOW_WIDTH * 2, -WINDOW_HEIGHT * 2, pos.y * 1 / 2).draw(WINDOW_WIDTH / 8);
		pos += Vec2(30, 30);
	});
}
/*
void EffectManager::fadeGraph(Texture&& tex, std::function<bool()>&& isDeleteFunc)
{
	Create<EffectPart>(216000, Vec2(WINDOW_WIDTH / 64, 0), [isDelete = isDeleteFunc](int32& count, Vec2& pos, Texture& tex) {
		if (isDelete()) {
			count = -1;
			return;
		}

		tex.resize(WINDOW_WIDTH, WINDOW_HEIGHT * 2 / 3).draw(pos, Alpha(count));
		if (count < 255) count++;
	}, std::move(tex));
}
*/
void EffectManager::update()
{
	TaskCall::All::Update();
	Task::All::Update();
}
