#include"Signboard.h"

Signboard::Signboard(const CVector2D& pos)
	:Base(eType_Signboard)
{
	//âÊëúï°êª
	m_img = COPY_RESOURCE("Signboard", CImage);
	m_pos = pos;
	m_img.SetSize(128, 170);
	m_img.SetCenter(64, 170);
}

void Signboard::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
}