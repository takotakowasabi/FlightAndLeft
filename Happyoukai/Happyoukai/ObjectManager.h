#pragma once
#include <memory>
#include <forward_list>
#include "Object.h"
#include "AddRequestListener.h"

class ObjectManager : public AddRequestListner
{
public:
	void update();
	void draw() const;

	void addObject(spObject) override;

private:
	static void callUpdate(std::forward_list<spObject>& objList);
	static void callDraw(const std::forward_list<spObject>& objList);

	void collisionJudge();
	static void judgeLists(std::forward_list<spObject>& objList1, std::forward_list<spObject>& objList2);

	std::forward_list<spObject> _friendObjects;
	std::forward_list<spObject> _friendCharacters;
	std::forward_list<spObject> _enemyObjects;
	std::forward_list<spObject> _enemyCharacters;
};