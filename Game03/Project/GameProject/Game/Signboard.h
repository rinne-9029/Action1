#pragma once
#include"../Base/Base.h"
class Signboard :public Base {
private:
	//�摜�I�u�W�F�N�g
	CImage m_img;

public:
	Signboard(const CVector2D& png);
	void Draw();
};