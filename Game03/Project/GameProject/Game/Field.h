#pragma once
#include "../Base/Base.h"

class Field : public Base {
private:
	//�摜�I�u�W�F�N�g(�ŉ��i)
	CImage m_background;
public:
	//�R���X�g���N�^
	Field();
	//�`��
	void Draw();
};