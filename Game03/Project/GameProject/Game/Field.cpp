#include "Field.h"

Field::Field(int layer):Base(eType_Field,layer)
{
	m_background = COPY_RESOURCE("Background", CImage);
}

void Field::Draw()
{
	m_background.Draw();
}