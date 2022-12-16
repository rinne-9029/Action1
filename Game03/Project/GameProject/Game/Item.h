#pragma once

#include"../Base/Base.h"

class Item : public Base {
private:
	enum {
		eAnimidle = 0,
		eAnimhit,
	};
	CImage m_img;
public:
	Item(int layer,const CVector2D& pos);
	void Update();
	void Draw();
	void Collision(Base* b);
};