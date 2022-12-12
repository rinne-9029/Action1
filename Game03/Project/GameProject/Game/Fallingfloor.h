#pragma once

#include"../Base/Base.h"

class Fallingfloor : public Base {
private:
	enum {
		eState_On,
		eState_Off,
	};
	CImage m_img;
	//��ԕϐ�
	int m_state;
	//�e��Ԗ�
	void StateOn();
	void StateOff();
public:
	Fallingfloor(const CVector2D&pos);
	void Update();
	void Draw();
	void Collision(Base* b);
};