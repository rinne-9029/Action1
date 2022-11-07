#include "Field.h"

Field::Field():Base(eType_Field)
{
	m_background = COPY_RESOURCE("Background", CImage);
}

void Field::Draw()
{
	m_background.Draw();
}