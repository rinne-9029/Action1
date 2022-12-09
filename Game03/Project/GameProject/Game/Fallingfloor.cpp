#include"Fallingfloor.h"
#include"Player.h"
#include"Game.h"

//アニメーション設定
static TexAnim _falling_floor[] = {
	{0,1},
	{1,1},
	{2,1},
	{3,1},
};

TexAnimData fallingfloorAnimData[] = {
	ANIMDATA(_falling_floor),
};

//状態設定
void Fallingfloor::StateOn()
{
	//アニメーション更新
	m_img.UpdateAnimation();
}

void Fallingfloor::StateOff()
{
	//重力による落下
	m_vec.y += GRAVITY;
	m_pos += m_vec;
}


Fallingfloor::Fallingfloor(const CVector2D& pos)
	:Base(eType_Fallingfloor)
{
	m_img.Load("Image/Fallingfloor/On.png", fallingfloorAnimData, 32, 10);
	//座標設定
	m_pos = pos;
	//再生アニメーション
	m_img.ChangeAnimation(0);
	//中心設定
	m_img.SetCenter(16, 5);
	m_rect = CRect(-16, -5, 16, 5);
	m_state = eState_On;
}


void Fallingfloor::Update()
{
	switch (m_state) {
	case eState_On:
		StateOn();
		break;
	case eState_Off:
		StateOff();
		break;
	}


	
}


void Fallingfloor::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
	DrawRect();
}


void Fallingfloor::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Player:
		if (Base::CollisionRect(this, b)) {
			m_state = eState_Off;
		}
		break;
	}
}
