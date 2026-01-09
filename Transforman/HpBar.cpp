#include "HpBar.h"
#include <DxLib.h>
#include <cassert>

namespace
{
	constexpr int graph_width = 60;//HPバーと幅
	constexpr int graph_height = 30;//HPバーと高さ

	//描画位置オフセット
	constexpr int draw_offset_x = 170;
	constexpr int draw_offset_y = 50;

	constexpr int pinch_hp = 2;//ピンチと判断するHP
	constexpr int normal_hp = 3;//通常と判断するHP

	constexpr int normal_hp_offset = 95;//通常HPの描画位置オフセット
	constexpr int next_hp_offset = 25;//次のHPの描画位置オフセット

	constexpr double graph_size = 5.0; //拡大率
}

HpBar::HpBar(int maxHitPoint) :
	UserInterface({0,0}),
	m_hitPoint(0),
	m_maxHitPoint(maxHitPoint)
{
	int handle = -1;
	handle = LoadGraph("img/game/Player/HP_Bar_Frame.png");//HPバーの枠
	m_handles.push_back(handle);
	assert(handle >= 0);//ハンドルnullチェック

	handle = LoadGraph("img/game/Player/HP_Bar_Background.png");//HPバーの背景
	m_handles.push_back(handle);
	assert(handle >= 0);//ハンドルnullチェック

	handle = LoadGraph("img/game/Player/HP_Bar_Heart.png");//HPバーのハート
	m_handles.push_back(handle);
	assert(handle >= 0);//ハンドルnullチェック

	handle = LoadGraph("img/game/Player/HP_Bar_Normal.png");//HPバーの通常カラー
	m_handles.push_back(handle);
	assert(handle >= 0);//ハンドルnullチェック

	handle = LoadGraph("img/game/Player/HP_Bar_Pinch.png");//HPバーのピンチ時カラー
	m_handles.push_back(handle);
	assert(handle >= 0);//ハンドルnullチェック
	
	//HPを設定
	m_hitPoint = m_maxHitPoint;
}

HpBar::~HpBar()
{
}

void HpBar::Update()
{
}

void HpBar::Update(std::shared_ptr<Player> pPlayer)
{
	m_hitPoint = pPlayer->GetHitPoint();//HPを更新
}

void HpBar::Draw()
{
#ifdef _DEBUG
	DrawFormatString(0, 200, 0xffffff, "PlayerHitPoint : %d", m_hitPoint);
#endif // _DEBUG

	////UIの描画
	
	//HPの枠の描画
	DrawRotaGraph(
		static_cast<int>(m_pos.x + draw_offset_x),
		static_cast<int>(m_pos.y + draw_offset_y),
		5.0, 0.0,
		m_handles[static_cast<int>(handleNomber::Frame)],
		true, false);

	//ハートの描画
	DrawRotaGraph(
		static_cast<int>(m_pos.x + draw_offset_x),
		static_cast<int>(m_pos.y + draw_offset_y),
		5.0, 0.0,
		m_handles[static_cast<int>(handleNomber::Heart)],
		true, false);

	switch (m_hitPoint)
	{
	case 1:
	case 2:
		for (int i = 0; i < m_hitPoint; ++i)
		{
			//ピンチ時のHPの描画
			DrawRotaGraph(
				static_cast<int>(m_pos.x + draw_offset_x + i * next_hp_offset),
				static_cast<int>(m_pos.y + draw_offset_y),
				graph_size, 0.0,
				m_handles[static_cast<int>(handleNomber::Pinch)],
				true, false);
		}
		break;
	case 3:
	case 4:
	case 5:
		for (int i = 0; i < m_hitPoint; ++i)
		{
			//ノーマルHP描画
			DrawRotaGraph(
				static_cast<int>(m_pos.x + normal_hp_offset + i * next_hp_offset),
				static_cast<int>(m_pos.y + draw_offset_y),
				graph_size, 0.0,
				m_handles[static_cast<int>(handleNomber::Normal)],
				true, false);
		}
		break;
	}
	//HPバーの描画
	

	
}
