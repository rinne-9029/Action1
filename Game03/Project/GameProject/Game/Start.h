#pragma once
#include"../Base/Base.h"

class Start :public Base {
private:
	//画像オブジェクト
	CImage m_img;

public:
	Start(const CVector2D& png);
	void Draw();
};