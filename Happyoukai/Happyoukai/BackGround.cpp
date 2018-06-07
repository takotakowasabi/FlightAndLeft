#include "BackGround.h"
#include "Define.h"

BackGround::BackGround()
{
	Image image1(WINDOW_WIDTH, WINDOW_HEIGHT, HSV(177, 55, 100));
	Image image2(WINDOW_WIDTH, WINDOW_HEIGHT, Color(248));
	_backGround = Texture(image1);
	_uiBase = Texture(image2);
}

void BackGround::update()
{
}

void BackGround::drawBackGround() const
{
	Graphics2D::SetStencilState(StencilState::Test(StencilFunc::Equal));

	_backGround.draw();

	Graphics2D::SetStencilState(StencilState::None);
}

void BackGround::drawUIBase() const
{
	Graphics2D::SetStencilState(StencilState::Test(StencilFunc::NotEqual));

	_uiBase.draw();

	Graphics2D::SetStencilState(StencilState::None);
}
