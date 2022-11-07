#pragma once
#include "../Base/Base.h"

class Field : public Base {
private:
	//画像オブジェクト(最遠景)
	CImage m_background;
public:
	//コンストラクタ
	Field();
	//描画
	void Draw();
};