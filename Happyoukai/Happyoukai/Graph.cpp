#include "Graph.h"
#include <algorithm>
#include <utility>

UpdateCountFunc::UpdateCountFunc(GraphCountFunc func) :
	_count(0),
	_func(func)
{
}

bool UpdateCountFunc::operator()(std::shared_ptr<Graph> graph)
{
	return _func(graph, _count);
}

void GraphManager::update()
{
	std::for_each(_graphs.begin(), _graphs.end(), [](std::shared_ptr<Graph> graph) {
		auto newEnd = std::remove_if(graph->updateFuncs.begin(), graph->updateFuncs.end(), [graph](GraphFunc& gf) {
			return !gf(graph);
		});
		graph->updateFuncs.erase(newEnd, graph->updateFuncs.end());
	});
}

void GraphManager::draw() const
{
	std::for_each(_graphs.begin(), _graphs.end(), [](std::shared_ptr<Graph> graph) {
		graph->texture 
			.resize(graph->size)
			.draw(graph->upLeft, Alpha(graph->transparrency));
	});
}

size_t GraphManager::add(Texture && texture, Vec2 && upLeft, Vec2 && size, bool fade)
{
	_graphs.push_back(std::make_shared<Graph>());
	std::shared_ptr<Graph> spGraph = _graphs.back();
	spGraph->texture = texture;
	spGraph->upLeft = upLeft;
	spGraph->size = size;
	if (fade) {
		spGraph->transparrency = 0;
		fadeIn(_graphs.size() - 1);
	}
	else spGraph->transparrency = 255;
	return _graphs.size() - 1;
}

size_t GraphManager::addC(Texture && texture, Vec2 && center, Vec2 && size, bool fade)
{
	return add(
		std::forward<Texture>(texture),
		Vec2(center - size / 2),
		std::forward<Vec2>(size),
		fade
	);
}

void GraphManager::changeUpLeft(size_t num, Vec2 upLeft)
{
	_graphs[num]->upLeft = upLeft;
}

void GraphManager::changeCenter(size_t num, Vec2 center)
{
	_graphs[num]->upLeft = center - _graphs[num]->size / 2;
}

void GraphManager::moveUpLeft(size_t num, Vec2 deltaVector)
{
	_graphs[num]->upLeft += deltaVector;
}

void GraphManager::fadeOut(size_t num)
{
	_graphs[num]->updateFuncs.push_back([](std::shared_ptr<Graph> graph) {
		if (graph->transparrency <= 0) return false;
		graph->transparrency-=3;
		return true;
	});
}

void GraphManager::fadeIn(size_t num)
{
	_graphs[num]->updateFuncs.push_back([](std::shared_ptr<Graph> graph) {
		if (graph->transparrency >= 255) return false;
		graph->transparrency+=3;
		return true;
	});
}

void GraphManager::flash(size_t num)
{
	_graphs[num]->updateFuncs.push_back(UpdateCountFunc([](std::shared_ptr<Graph> graph, int32& count) {
		if(static_cast<int>(count / 255) % 2) graph->transparrency = 255 - (count % 255);
		else graph->transparrency = count % 255;
		count += 17;
		return true;
	}));
}
