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

class UI2 :public Base {
public:
	CImage m_img;
	int kosu;
public:
	UI2();
	void Update();
	void Draw();
};