#include "TextManager.h"
#include <DxLib.h>
#include <cassert>

TextManager::TextManager()
{
	int handle = -1;
	m_handles.push_back(handle);//ƒ_ƒ~[

	handle = LoadGraph("img/game/Text/move.png");
	assert(handle >= 0);
	m_handles.push_back(handle);
}

void TextManager::Create(int handle, TextType type)
{
	switch (type)
	{
	case TextType::Move:

		break;
	}
}

void TextManager::Update()
{

}

void TextManager::Draw()
{
	
}