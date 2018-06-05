#include "ObjectManager.h"
#include <algorithm>

void ObjectManager::update()
{
	callUpdate(_friendObjects);
	callUpdate(_friendCharacters);
	callUpdate(_enemyObjects);
	callUpdate(_enemyCharacters);
	collisionJudge();
}

void ObjectManager::draw() const
{
	callDraw(_friendObjects);
	callDraw(_friendCharacters);
	callDraw(_enemyObjects);
	callDraw(_enemyCharacters);
}

void ObjectManager::addObject(spObject spO)
{
	switch (spO->getGroup()) {
	case ObjectGroup::friendObject: _friendObjects.push_front(spO); break;
	case ObjectGroup::friendCharacter: _friendCharacters.push_front(spO); break;
	case ObjectGroup::enemyObject: _enemyObjects.push_front(spO); break;
	case ObjectGroup::enemyCharacter: _enemyCharacters.push_front(spO); break;
	}
}

void ObjectManager::callUpdate(std::forward_list<spObject>& objList)
{
	auto result = std::remove_if(objList.begin(), objList.end(), [](spObject spO) {
		return spO->update();
	});
	if(result != objList.end()) objList.erase_after(result, objList.end());
}

void ObjectManager::callDraw(const std::forward_list<spObject>& objList)
{
	std::for_each(objList.begin(), objList.end(), [](spObject spO) {
		spO->draw();
	});
}

void ObjectManager::collisionJudge()
{

}

void ObjectManager::judgeLists(std::forward_list<spObject>& objList1, std::forward_list<spObject>& objList2)
{
	std::for_each(objList1.begin(), objList2.end(), [&objList2](spObject spO1) {
		std::for_each(objList2.begin(), objList2.end(), [&spO1](spObject spO2) {
			double distance = spO1->getPosition().distanceFrom(spO2->getPosition());
			if (distance < spO1->getRadius() + spO2->getRadius()) {
				spObject spO = spO1;
				spO1->collision(spO2);
				spO2->collision(spO);
			}
		});
	});
}
