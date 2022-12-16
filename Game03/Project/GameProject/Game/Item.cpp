#include"Item.h"
#include"Map.h"


//�A�j���[�V�����ݒ�
static TexAnim _item_idle[] = {
	{ 0,3 },
	{ 1,3 },
	{ 2,3 },
	{ 3,3 },
	{ 4,3 },
	{ 5,3 },
	{ 6,3 },
	{ 7,3 },
	{ 8,3 },
	{ 9,3 },
};

static TexAnim _item_hit[] = {
	{ 10,2 },
	{ 11,2 },
	{ 12,2 },
	{ 13,2 },
};

TexAnimData itemAnimData[] = {
	ANIMDATA(_item_idle),
	ANIMDATA(_item_hit),
};



Item::Item(int layer,const CVector2D& pos)
	:Base(eType_Item,layer)
{
	//�摜�ǂݍ���
	m_img.Load("Image/Jumpitem/Item.png", itemAnimData, 18, 18);
	//�Đ��A�j���[�V����
	m_img.ChangeAnimation(0);
	m_img.SetSize(32, 32);
	m_img.SetCenter(16,16);
    m_rect = CRect(-10, -10, 10, 10);

	m_pos = pos;
}

void Item::Update()
{
	//�A�j���[�V�����Đ�
	m_img.UpdateAnimation();
	//�A�j���[�V�����I����
if (m_img.CheckAnimationEnd()) {
	//�A�C�e���폜
    SetKill();
}


}

void Item::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
	//DrawRect();
}

void Item::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Player:
		if (Base::CollisionRect(this, b)) {
			m_img.ChangeAnimation(eAnimhit, false);
			
		}
		
	}
}
