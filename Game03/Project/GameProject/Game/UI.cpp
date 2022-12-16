#include "UI.h"
#include"GameData.h"

UI::UI(int layer) :Base(eType_UI,layer) 
{
	m_img.Load("Image/UI/Text.png");
}

void UI::Update()
{
	cnt++;
	if (cnt >= 60) {
		GameData::s_count += 1;
		cnt = 0;
	}
}

void UI::Draw()
{
	int count = GameData::s_count;
	for (int i = 0; i < 4; i++, count /= 10) {
		int s = count % 10;
		m_img.SetRect(8 * s, 30, 8 * s + 8, 40);
		m_img.SetSize(32, 32);
		m_img.SetPos(100 - 32 * i, 0);
		m_img.Draw();
	}
}

UI2::UI2(int layer) :Base(eType_UI2,layer)
{
	m_img.Load("Image/UI/LIFE.png");
}

void UI2::Update()
{
}

void UI2::Draw()
{
	for (int i = GameData::s_kosu; i > 0; i--) {
		m_img.SetSize(32, 32);
		m_img.SetPos(300 - 32 * i, 0);
		m_img.Draw();
	}
}
