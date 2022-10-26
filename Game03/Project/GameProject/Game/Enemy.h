#pragma once
#include "../Base/Base.h"

class Enemy : public Base {
private:
	//ó‘Ô
	enum {
		eState_Idle,
		eState_Attack,
		eState_Damage,
		eState_Down,
		eState_Wait
	};
	//ó‘Ô•Ï”
	int m_state;
	int m_cnt;
	int m_attack_no;
	int m_damage_no;
	int m_hp;


	CImage m_img;
	bool m_flip;
	bool m_is_ground;
	void StateIdle();
	void StateAttack();
	void StateWait();
	void StateDown();
	void StateDamage();
public:
	Enemy(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
};