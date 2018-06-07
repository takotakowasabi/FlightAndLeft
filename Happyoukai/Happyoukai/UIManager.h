#pragma once
#include "UserInterface.h"
#include <vector>

class UIManager{
public:
	void update();
	void draw() const;

	void transformStart(spFieldSize fieldSize, Vec2 direct);
	void transform(int32 count);

	void addUI(spUI ui);

private:
	std::vector<spUI> _UIs;

};