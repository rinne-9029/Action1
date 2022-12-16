#pragma once
#include"../Base/Base.h"
class Goal :public Base {
private:
	//画像オブジェクト
	CImage m_img;

public:
	Goal(int layer,const CVector2D& png);
	void Draw();
};