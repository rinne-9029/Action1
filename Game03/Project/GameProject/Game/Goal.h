#pragma once
#include"../Base/Base.h"
class Goal :public Base {
private:
	//�摜�I�u�W�F�N�g
	CImage m_img;

public:
	Goal(int layer,const CVector2D& png);
	void Draw();
};