#pragma once

#include"../Base/Base.h"

class Fallingfloor : public Base {
private:
	enum {
		eState_On,
		eState_Off,
	};
	CImage m_img;
	//ó‘Ô•Ï”
	int m_state;
	//Šeó‘Ô–¼
	void StateOn();
	void StateOff();
public:
	Fallingfloor(const CVector2D&pos);
	void Update();
	void Draw();
	void Collision(Base* b);
};