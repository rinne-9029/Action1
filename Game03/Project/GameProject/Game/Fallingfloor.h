#pragma once

#include"../Base/Base.h"

class Fallingfloor : public Base {
private:
	enum {
		eState_On,
		eState_Off,
	};
	CImage m_img;
	//状態変数
	int m_state;
	//各状態名
	void StateOn();
	void StateOff();
public:
	Fallingfloor(int layer,const CVector2D&pos);
	void Update();
	void Draw();
	void Collision(Base* b);
};