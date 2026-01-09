#include "HpBar.h"
#include <DxLib.h>
#include <cassert>

namespace
{
	constexpr int graph_width = 60;
	constexpr int graph_height = 30;
}

HpBar::HpBar(int maxHitPoint,int srcX,int srcY) :
	UserInterface({0,0}),
	m_hitPoint(0),
	m_maxHitPoint(maxHitPoint)
{
	int handle = -1;
	handle = LoadGraph("img/game/Player/HP_Bar_Frame.png");//HPバーの枠
	m_handles.push_back(handle);
	assert(handle >= 0);//ハンドルnullチェック

	handle = LoadGraph("img/game/Player/HP_Bar_Background");//HPバーの背景
	assert(handle >= 0);//ハンドルnullチェック

	handle = LoadGraph("img/game/Player/HP_Bar_Normal");//HPバーの通常カラー
	assert(handle >= 0);//ハンドルnullチェック

	handle = LoadGraph("img/game/Player/HP_Bar_Pinch");//HPバーのピンチ時カラー
	assert(handle >= 0);//ハンドルnullチェック
	
	//HPを設定
	m_hitPoint = m_maxHitPoint;
	//切り取りサイズを設定
	m_srcX = srcX;
	m_srcY = srcY;
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
	
	for (auto& handle : m_handles)
	{
		////UIの描画
		//DrawRectRotaGraph(
		//	static_cast<int>(m_pos.x),
		//	static_cast<int>(m_pos.y),
		//	m_srcX, m_srcY,
		//	);
	}
	
}
