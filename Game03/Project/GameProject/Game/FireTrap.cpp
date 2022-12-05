#include "FireTrap.h"


//�A�j���[�V�����ݒ�
static TexAnim _fire_trap[] = {
	{ 0,6 },
	{ 1,6 },
	{ 2,6 },
	{ 3,6 },
	{ 4,4 },
	{ 5,4 },
	{ 6,4 },
	{ 7,4 },
	{ 8,4 },
	{ 9,4 },
	{ 10,4 },
	{ 11,4 },
};

TexAnimData firetrapAnimData[] = {
	ANIMDATA(_fire_trap),
};


FireTrap::FireTrap(const CVector2D& pos,int attack_no):
	Base(eType_FireTrap)
{
	//�摜�ǂݍ���
	m_img.Load("Image/FireTrap/FireTrap.png", firetrapAnimData, 32, 64);
	//�Đ��A�j���[�V����
	m_img.ChangeAnimation(0);
	m_img.SetCenter(16, 64);
	
	m_pos = pos;
	//�U���ԍ�
	m_attack_no = attack_no;
    //�t���[��
	cnt = 0;
}

void FireTrap::Update()
{
	m_img.UpdateAnimation();
	cnt++;
	if (cnt >= 24) {
		m_rect = CRect(-5, -64, 5, 0);
	}
	if (cnt == 56) {
		cnt = 0;
		m_rect = CRect(-5, 3, 5, 0);
	}
}

void FireTrap::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
	//DrawRect();
}

void FireTrap::Collision(Base* b)
{
}
