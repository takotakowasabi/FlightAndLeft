#include "UIManager.h"
#include <algorithm>

void UIManager::update()
{
	std::for_each(_UIs.begin(), _UIs.end(), [](spUI ui) {
		ui->update();
	});
}

void UIManager::draw() const
{
	std::for_each(_UIs.begin(), _UIs.end(), [](spUI ui) {
		ui->draw();
	});
}

void UIManager::transformStart(spFieldSize fieldSize, Vec2 direct)
{
	std::for_each(_UIs.begin(), _UIs.end(), [fieldSize, direct](spUI ui) {
		ui->transformStart(fieldSize, direct);
	});
}

void UIManager::transform(int32 count)
{
	std::for_each(_UIs.begin(), _UIs.end(), [count](spUI ui) {
		ui->transform(count);
	});
}

void UIManager::addUI(spUI ui)
{
	_UIs.push_back(ui);
}
