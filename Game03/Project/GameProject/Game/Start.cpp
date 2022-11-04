#include"Start.h"

Start::Start(const CVector2D& pos)
	:Base(eType_Start)
{
	//âÊëúï°êª
	m_img = COPY_RESOURCE("Start", CImage);
	m_pos = pos;
	m_img.SetCenter(32, 64);
	m_rect = CRect(-22, -45, 22, 0);
}

void Start::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
	//DrawRect();
}
