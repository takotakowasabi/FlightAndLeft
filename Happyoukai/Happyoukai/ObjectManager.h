#pragma once
#include <memory>
#include <list>
#include "Object.h"
#include "AddRequestListener.h"

class ObjectManager : public AddRequestListner
{
public:
	void update();
	void draw() const;

	spObject addObject(spObject) override;

private:
	static void callUpdate(std::list<spObject>& objList);
	static void callDraw(const std::list<spObject>& objList);

	void collisionJudge();
	static void judgeLists(std::list<spObject>& objList1, std::list<spObject>& objList2);

	std::list<spObject> _neutralObjects;
	std::list<spObject> _friendObjects;
	std::list<spObject> _friendCharacters;
	std::list<spObject> _enemyObjects;
	std::list<spObject> _enemyCharacters;
};