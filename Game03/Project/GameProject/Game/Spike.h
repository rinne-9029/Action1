#pragma once
#include"../Base/Base.h"

class Spike : public Base {
private:
	int Spike_Type;
	CImage m_img;
	int m_attack_no;
public:
	Spike(const CVector2D& pos,int spike_type);
	void Draw();
	void Collision(Base* b);
	int GetAttackNo() {
		return m_attack_no;
	}
};