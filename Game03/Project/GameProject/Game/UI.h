#pragma once
#include"../Base/Base.h"

class UI :public Base {
public:
	CImage m_img;
	int cnt;
public:
	UI(int layer);
	void Update();
	void Draw();
};

class UI2 :public Base {
public:
	CImage m_img;
	int kosu;
public:
	UI2(int layer);
	void Update();
	void Draw();
};