#pragma once
#include"../Base/Base.h"

class UI :public Base {
public:
	CImage m_img;
	int cnt;
public:
	UI();
	void Update();
	void Draw();
};
