#include "BackGround.h"
#include <DxLib.h>
#include "General/GameConstants.h"

namespace
{
	constexpr double graph_scale = 0.8;//‰æ‘œ‚ÌŠg‘å”{—¦
	constexpr double graph_angle = 0.0;//‰æ‘œ‚ÌŠp“x
}

BackGround::BackGround() :
	m_pos(0.0f,0.0f)
{
	m_handle = LoadGraph("img/game/Map/background.png");
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
	//”wŒi
	DrawRotaGraph(m_pos.x + Graphic::screen_width * 0.5f ,
					m_pos.y + Graphic::screen_height * 0.5f,
					graph_scale, graph_angle,
					m_handle, true, false);
}
