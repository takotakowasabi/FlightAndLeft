#include "UserInterface.h"

class ReturnTitle : public UserInterface {
public:
	static const Vec2 DEFAULT_POSITION;

	ReturnTitle(std::shared_ptr<bool> returnTitleFlag, Vec2 position = DEFAULT_POSITION);

	void update() override;
	void draw() const override;

	void transform(int32 count) override;
	void transformStart(spFieldSize fieldSize, Vec2 direct) override;

private:
	std::shared_ptr<bool> _returnTitleFlag;
	Font _font;
	Vec2 _position;
	Vec2 _goalPosition;
	bool _onMouse;

};