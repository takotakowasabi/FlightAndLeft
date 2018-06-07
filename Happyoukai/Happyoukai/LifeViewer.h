#pragma once
#include "UserInterface.h"

class LifeViewer : public UserInterface {
public:
	static const Vec2 DEFAULT_POSITION;

	LifeViewer(std::shared_ptr<int32> life, Vec2 position = DEFAULT_POSITION);

	void update() override;
	void draw() const override;

	void transform(int32 count) override;
	void transformStart(spFieldSize fieldSize, Vec2 direct) override;

private:
	Texture _lifeImage;
	Texture _noLifeImage;
	Vec2 _position;
	Vec2 _goalPosition;
	std::shared_ptr<int32> _life;

};