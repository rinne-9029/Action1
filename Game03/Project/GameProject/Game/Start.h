#pragma once
#include"../Base/Base.h"

class Start :public Base {
private:
	//�摜�I�u�W�F�N�g
	CImage m_img;

public:
	Start(const CVector2D& png);
	void Draw();
};