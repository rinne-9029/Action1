#include "FireTrap.h"
#include"Game.h"


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


FireTrap::FireTrap(const CVector2D& pos):
	Base(eType_FireTrap)
{
	//�摜�ǂݍ���
	m_img.Load("Image/FireTrap/FireTrap.png", firetrapAnimData, 32, 64);
	//�Đ��A�j���[�V����
	m_img.ChangeAnimation(0);
	m_img.SetCenter(16, 5);
	//m_img.SetSize(64, 128);
	m_rect = CRect(-16, -5, 16, 5);
	m_pos = pos;

}

void FireTrap::Update()
{
	m_img.UpdateAnimation();
}

void FireTrap::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
}

void FireTrap::Collision(Base* b)
{

}
