#pragma once
#include"../Base/Base.h"
class Signboard :public Base {
private:
	//画像オブジェクト
	CImage m_img;

public:
	Signboard(const CVector2D& png);
	void Draw();
};