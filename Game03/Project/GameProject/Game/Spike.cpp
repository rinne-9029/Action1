#include"Spike.h"

Spike::Spike(const CVector2D& pos,int spike_type)
    :Base(eType_Spike)
{
	//Spike_Type = spike_type;
	switch (spike_type) {
	case 0:
		m_img = COPY_RESOURCE("Spikeup", CImage);
    //中心設定
	m_img.SetCenter(0,32);
	//矩形当たり判定
	m_rect = CRect(0, -16, 32, 0);
		break;
	case 1:
		m_img = COPY_RESOURCE("Spikedown", CImage);
		//中心設定
		m_img.SetCenter(0, 0);
		//矩形当たり判定
		m_rect = CRect(0, 0, 32, 16);
		break;
	case 2:
		m_img = COPY_RESOURCE("Spikeright", CImage);
		//中心設定
		m_img.SetCenter(0, 0);
		//矩形当たり判定
		m_rect = CRect(0, 0, 16, 32);
		break;
	case 3:
		m_img = COPY_RESOURCE("Spikeleft", CImage);
		//中心設定
		m_img.SetCenter(32, 0);
		//矩形当たり判定
		m_rect = CRect(0, 0, -16, 32);
		break;
	}
	m_pos = pos;
	//大きさ
	//m_img.SetSize(32, 32);
	

}

void Spike::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
	//DrawRect();
}

void Spike::Collision(Base* b)
{

}
