#pragma once
#include <Siv3D.hpp>
#include <vector>
#include <memory>
#include <functional>

/*
method
	フェード
	移動
	アクション
	中心表示
*/

struct Graph;

using GraphFunc = std::function<bool(std::shared_ptr<Graph>)>;
using GraphCountFunc = std::function<bool(std::shared_ptr<Graph>, int32&)>;

class UpdateCountFunc {
private:
	int32 _count;
	GraphCountFunc _func;
public:
	UpdateCountFunc(GraphCountFunc);

	bool operator()(std::shared_ptr<Graph>);
};

struct Graph {
	Texture texture;
	Vec2 upLeft;
	Vec2 size;
	int32 transparrency;
	int32 rotateAngle;
	bool deleteFlag;
	std::vector<GraphFunc> updateFuncs;
};

class GraphManager {
public:
	void update();
	void draw() const;

	size_t add(Texture&& texture, Vec2&& upLeft, Vec2&& size, bool fade = false);
	size_t addC(Texture&& texture, Vec2&& center, Vec2&& size, bool fade = false);
	
	void changeUpLeft(size_t num, Vec2 upLeft);
	void changeCenter(size_t num, Vec2 center);
	void moveUpLeft(size_t num, Vec2 deltaVector);

	void rotate(size_t num, int32 deltaAngle);
	void rotateAt(size_t num, int32 angle);

	void fadeOut(size_t num);
	void fadeIn(size_t num);
	void flash(size_t num);
	void deleteGraph(size_t num);

private:
	std::vector<std::shared_ptr<Graph>> _graphs;
};

using spGraphManager = std::shared_ptr<GraphManager>;