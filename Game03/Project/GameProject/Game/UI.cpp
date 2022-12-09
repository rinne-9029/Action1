#include "UI.h"
#include"GameData.h"

UI::UI() :Base(eType_UI) 
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
