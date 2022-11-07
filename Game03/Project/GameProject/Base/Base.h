#pragma once
#include<GLLibrary.h>
//�d�͉����x
#define GRAVITY (9.8f/20)
enum {
	eType_Field,
	eType_Goal,
	eType_Start,
	eType_Signboard,
    eType_Player,
	eType_Enemy,
	eType_Fallingfloor,
	eType_FireTrap,
	eType_Player_Attack,
	eType_Enemy_Attack,
	eType_Effect,
    eType_UI,
	eType_Scene,
	
};

class Base {
public:
	//�I�u�W�F�N�g�̎��
	int m_type;
	//���W�f�[�^
	CVector2D m_pos; 
	CVector2D m_pos_old;
	//���a
	float m_rad;
	//�ړ��x�N�g��
	CVector2D m_vec;
	//�X�N���[���l
	static CVector2D m_scroll;
	//�폜�t���O
	bool m_kill;
	//�I�u�W�F�N�g�̃��X�g
	static std::list<Base*>m_list;
	//�Z�`
	CRect m_rect;

public:
	//type�I�u�W�F�N�g�̎��
	Base(int type); //�R���X�g���N�^
	virtual~Base(); //�f�X�g���N�^
	virtual void Update(); //�X�V����
	virtual void Draw(); //�`�揈��
	virtual void Collision(Base* b);
	//�폜�t���OON
	void SetKill() { m_kill = true; }
	//�Z�`���m�̔���
	static bool CollisionRect(Base* b1, Base* b2);
	//�Z�`�̕\��
	void DrawRect();

	static CVector2D GetScreenPos(const CVector2D& pos);
	//�S�ẴI�u�W�F�N�g�̍X�V
	static void UpdateAll();
	//�S�ẴI�u�W�F�N�g�̕`��
	static void DrawAll();
	//�S�ẴI�u�W�F�N�g�̓����蔻�茟��
	   static void CollisionAll();
	   //�폜�`�F�b�N
	   static void CheckKillAll();
	//�I�u�W�F�N�g�̒ǉ�
 static void Add(Base* b);
 //�S�I�u�W�F�N�g�̍폜
 static void KillAll();
 //�~���m�̏Փ�
 static bool CollisionCircle(Base* b1, Base* b2);
 Base* Base::FindObject(int type);
};