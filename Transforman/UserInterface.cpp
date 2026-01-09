#include "UserInterface.h"
#include <DxLib.h>

UserInterface::UserInterface(Vector2 pos, int handle):
	m_pos(pos),m_handle(handle)
{

}

UserInterface::~UserInterface()
{

}

void UserInterface::Update()
{

}

void UserInterface::Draw()
{
	//UI‚Ì•`‰æ
	DrawRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), 1.0, 0.0, m_handle, true, false);
}