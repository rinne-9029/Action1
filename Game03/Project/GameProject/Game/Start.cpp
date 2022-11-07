#include"Start.h"

Start::Start(const CVector2D& pos)
	:Base(eType_Start)
{
	//‰æ‘œ•¡»
	m_img = COPY_RESOURCE("Start", CImage);
	m_pos = pos;
	m_img.SetSize(128, 128);
	m_img.SetCenter(70, 113);
}

void Start::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
}
