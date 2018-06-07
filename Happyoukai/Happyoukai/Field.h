#pragma once
#include <Siv3D.hpp>
#include <memory>

struct FieldSize {
	Vec2 upLeft;
	Vec2 downRight;
};

using spFieldSize = std::shared_ptr<FieldSize>;

class Field {
public:
	static const Vec2 DEFAULT_UPLEFT;
	static const Vec2 DEFAULT_DOWNRIGHT;

	Field(Vec2 upLeft = DEFAULT_UPLEFT, Vec2 downRight = DEFAULT_DOWNRIGHT);

	void update();
	void draw();

	void transform(const Vec2& centerPos, const Vec2& direct);
	bool isTransforming() {
		return _transformFlag;
	}

	const spFieldSize getSize() {
		return _fieldSize;
	}

private:
	bool _transformFlag;

	Vec2 _nowDirect;
	spFieldSize _fieldSize;
	spFieldSize _goalFieldSize;

	int32 _transformCount;
};