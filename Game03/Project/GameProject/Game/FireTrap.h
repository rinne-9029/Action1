#pragma once

#include"../Base/Base.h"

class FireTrap : public Base {
private:
	CImage m_img;
public:
	FireTrap(const CVector2D& pos);
	void Update();
	void Draw();
	void Collision(Base* b);
};