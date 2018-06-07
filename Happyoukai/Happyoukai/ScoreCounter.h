#pragma once
#include "UserInterface.h"

class ScoreCounter : public UserInterface {
public:
	static const Vec2 DEFAULT_POSITION;

	ScoreCounter(std::shared_ptr<int32> score, Vec2 position = DEFAULT_POSITION);

	void update() override;
	void draw() const override;

	void transform(int32 count) override;
	void transformStart(spFieldSize fieldSize, Vec2 direct) override;

private:
	Font _font;
	Vec2 _position;
	Vec2 _goalPosition;
	std::shared_ptr<int32> _score;
	int32 _drawScore;

};