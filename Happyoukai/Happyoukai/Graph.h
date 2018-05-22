#pragma once
#include <Siv3D.hpp>
#include <vector>
#include <memory>

/*
method
	フェード
	移動
	アクション
*/

struct Graph {
	Texture texture;
	Vec2 upLeft;
	Vec2 downRight;
	int32 fadeState;
	bool isFlashing;
};

class GraphManager {
public:
	void update();
	void draw() const;

	size_t add(Texture&& texture, Vec2&& upLeft, Vec2&& downRight, bool fade = false);
	void fadeOut(size_t num);
	void flash(size_t num);
	void move(Vec2 vec2);

private:
	std::vector<std::unique_ptr<Graph>> _graphs;
};