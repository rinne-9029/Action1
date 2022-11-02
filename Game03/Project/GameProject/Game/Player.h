#pragma once
#include"../Base/Base.h"

class Player : public Base {
private:
	//���
	enum {
		eState_Idle,
		eState_DoubleJump,
		eState_Damage,
		eState_Down
	};
	//��ԕϐ�
	int m_state;
	//���]�t���O
	bool m_flip;
	//���n�t���O
	bool m_is_ground;
	//�q�b�g�|�C���g
	int m_hp;
	//�W�����v��
	int jumpcount;
	//���G����
	int invincibility;
	CImage m_img;

	//�e��Ԃł̋���
	void StateIdle();
	void StateDoubleJump();
	void StateDamage();
	void StateDown();

public:
	Player(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
};