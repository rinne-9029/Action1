#pragma once

#include"../Base/Base.h"

class FireTrap : public Base {
private:
	CImage m_img;
	int m_attack_no;
public:
	FireTrap(const CVector2D& pos,int attack_no);
	void Update();
	void Draw();
	void Collision(Base* b);
	int GetAttackNo() {
		return m_attack_no;
	}
};