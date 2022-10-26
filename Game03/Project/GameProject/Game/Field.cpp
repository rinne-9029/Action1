#include "Field.h"

Field::Field():Base(eType_Field)
{
	m_ground_y = 540;
}

void Field::Draw()
{
	float sc;
	m_sky.Draw();
	sc = m_scroll.x / 4;
	m_town.SetRect(sc,0,sc + 1280, 720);
	m_town.Draw();

	sc = m_scroll.x;
	m_foreground.SetRect(sc, 0, sc + 1280, 720);
	m_foreground.Draw();
}