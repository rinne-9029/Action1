#include"Start.h"

Start::Start(const CVector2D& pos)
	:Base(eType_Start)
{
	//�摜����
	m_img = COPY_RESOURCE("Start", CImage);
	m_pos = pos;
	m_img.SetCenter(64, 56);
}

void Start::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
}
