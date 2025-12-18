#include "Text.h"
#include <DxLib.h>

namespace
{
	const Vector2 pos = { 400,500 };
}

Text::Text(int handle) :
	m_pos(pos),
	m_handle(handle)
{
	
}

Text::~Text()
{

}

void Text::Update()
{

}

void Text::Draw()
{
	DrawRotaGraph(m_pos.x, m_pos.y, 0.5, 0.0, m_handle, false);
}
