#pragma once
#include"../Base/Base.h"

class Effect : public Base {
private:
	//画像オブジェクト
	CImage m_img;
	//反転フラグ
	bool m_flip;
public:
	Effect(int layer,const char* name, const CVector2D& pos, bool);
	void Update();
	void Draw();
};