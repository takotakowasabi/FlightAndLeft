#include "UserInterface.h"

class LimitTimer : public UserInterface {
public:
	static const Vec2 DEFAULT_POSITION;

	LimitTimer(std::shared_ptr<int32> limitTime, Vec2 position = DEFAULT_POSITION);

	void update() override;
	void draw() const override;

	void transform(int32 count) override;
	void transformStart(spFieldSize fieldSize, Vec2 direct) override;

private:
	Font _font;
	Vec2 _position;
	Vec2 _goalPosition;

	int32 _limitMin;
	int32 _limitSec;
	std::shared_ptr<int32> _limitTime;

};