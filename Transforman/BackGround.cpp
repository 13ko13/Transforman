#include "BackGround.h"
#include <DxLib.h>
#include "General/GameConstants.h"
#include <cassert>

namespace
{
	constexpr double graph_scale = 0.8;//âÊëúÇÃägëÂî{ó¶
	constexpr double graph_angle = 0.0;//âÊëúÇÃäpìx
}

BackGround::BackGround() :
	m_pos(0.0f,0.0f)
{
	m_handle = LoadGraph("img/game/Map/background.png");
	//É`ÉFÉbÉN
	assert(m_handle >= 0);
}

BackGround::~BackGround()
{
	DeleteGraph(m_handle);
}

void BackGround::Update()
{

}

void BackGround::Draw()
{
	//îwåi
	DrawRotaGraph(m_pos.x + Graphic::screen_width * 0.5f ,
					m_pos.y + Graphic::screen_height * 0.5f,
					graph_scale, graph_angle,
					m_handle, true, false);
}
