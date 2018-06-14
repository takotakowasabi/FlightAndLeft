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
	std::for_each(_graphs.begin(), _graphs.end(), [](std::pair<int32, std::shared_ptr<Graph> > graph) {
		if (graph.second->deleteFlag) return;
		auto graphSec = graph.second;
		auto newEnd = std::remove_if(graph.second->updateFuncs.begin(), graph.second->updateFuncs.end(), [graphSec](GraphFunc& gf) {
			return !gf(graphSec);
		});

		graph.second->updateFuncs.erase(newEnd, graph.second->updateFuncs.end());
	});
}

void GraphManager::draw() const
{
	std::for_each(_graphs.begin(), _graphs.end(), [](std::pair<int32, std::shared_ptr<Graph> > graph) {
		if (graph.second->deleteFlag) return;
		graph.second->texture 
			.resize(graph.second->size)
			.rotate(Radians(graph.second->rotateAngle))
			.draw(graph.second->upLeft, Alpha(graph.second->transparrency));
	});
}

size_t GraphManager::add(Texture && texture, Vec2 && upLeft, Vec2 && size, bool fade)
{
	_graphs.emplace(_count, std::make_shared<Graph>());
	std::shared_ptr<Graph> spGraph = _graphs[_count];
	spGraph->texture = texture;
	spGraph->upLeft = upLeft;
	spGraph->size = size;
	if (fade) {
		spGraph->transparrency = 0;
		fadeIn(_count);
	}
	else spGraph->transparrency = 255;
	spGraph->rotateAngle = 0;
	spGraph->deleteFlag = false;

	return _count++;
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

void GraphManager::rotate(size_t num, int32 deltaAngle)
{
	_graphs[num]->rotateAngle += deltaAngle;
}

void GraphManager::rotateAt(size_t num, int32 angle)
{
	_graphs[num]->rotateAngle = angle;
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

void GraphManager::deleteGraph(size_t num)
{
	_graphs[num]->deleteFlag = true;
}
