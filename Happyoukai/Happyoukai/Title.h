#pragma once
#include "Define.h"
#include "Effect.h"
#include <memory>

class Title : public MyApp::Scene
{
public:
	// �N���X�̏��������Ɉ�x�����Ă΂��i�ȗ��j
	void init() override;

	// ���t���[�� updateAndDraw() �ŌĂ΂��
	void update() override;

	// ���t���[�� update() �̎��ɌĂ΂��
	void draw() const override;
private:
};