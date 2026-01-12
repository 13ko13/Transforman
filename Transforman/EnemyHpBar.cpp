#include "EnemyHpBar.h"
#include <DxLib.h>
#include <cassert>

namespace
{
	constexpr int graph_width = 60;//HPバーと幅
	constexpr int graph_height = 30;//HPバーと高さ

	//描画位置オフセット
	constexpr int draw_fir_offset_x = 43;
	constexpr int first_frame_offset_x = 1000;
	constexpr int draw_offset_y = 90;

	constexpr int pinch_hp = 2;//ピンチと判断するHP
	constexpr int normal_hp = 3;//通常と判断するHP

	constexpr int normal_hp_offset = 925;//通常HPの描画位置オフセット
	constexpr int next_hp_offset = 25;//次のHPの描画位置オフセット

	constexpr double graph_size = 5.0; //拡大率

	constexpr int hp_1 = 1;//HP1
	constexpr int hp_2 = 2;//HP2
	constexpr int hp_3 = 3;//HP3
	constexpr int hp_4 = 4;//HP4
	constexpr int hp_5 = 5;//HP5
	constexpr int hp_6 = 6;//HP6
	constexpr int hp_7 = 7;//HP7
	constexpr int hp_8 = 8;//HP8
	constexpr int hp_9 = 9;//HP9
	constexpr int hp_10 = 10;//HP10

	constexpr int first_frame_width = 20;//最初の枠の幅
	constexpr int last_frame_srcX = 40;//最後の枠の切り取り開始位置
	constexpr int last_frame_width = 20;//最後の枠の幅
	constexpr int draw_last_offset_x = 217;//最後の枠の描画位置オフセット
	constexpr int frame_height = 30;//枠の高さ
	constexpr int one_hp_width = 5;//1メモリの幅
	constexpr int empty_hp_offset_x = 15;//空HPの描画位置オフセット
	constexpr int pinch_hp_offset = 15;//ピンチ時HPの描画位置オフセット
}

EnemyHpBar::EnemyHpBar(int maxHitPoint) :
	UserInterface({ 0,0 }),
	m_currentHP(0),
	m_maxHP(maxHitPoint)
{
	int handle = -1;
	handle = LoadGraph("img/game/Enemy/HP_Bar_Frame.png");//HPバーの枠
	m_handles.push_back(handle);
	assert(handle >= 0);//ハンドルnullチェック

	handle = LoadGraph("img/game/Enemy/HP_Bar_Heart.png");//HPバーのハート
	m_handles.push_back(handle);
	assert(handle >= 0);//ハンドルnullチェック

	handle = LoadGraph("img/game/Enemy/HP_Bar_Normal.png");//HPバーの通常カラー
	m_handles.push_back(handle);
	assert(handle >= 0);//ハンドルnullチェック

	handle = LoadGraph("img/game/Enemy/HP_Bar_Pinch.png");//HPバーのピンチ時カラー
	m_handles.push_back(handle);
	assert(handle >= 0);//ハンドルnullチェック

	handle = LoadGraph("img/game/Enemy/HP_Bar_Empty.png");
	m_handles.push_back(handle);
	assert(handle >= 0);//ハンドルnullチェック

	//HPを設定
	m_currentHP = m_maxHP;

	m_pos = { first_frame_offset_x ,draw_offset_y };
}

EnemyHpBar::~EnemyHpBar()
{
	//画像の開放
	for (auto handle : m_handles)
	{
		DeleteGraph(handle);
	}
}

void EnemyHpBar::Update()
{
}

void EnemyHpBar::Update(int currentHP)
{
	m_currentHP = currentHP;//HPを更新
}

void EnemyHpBar::Draw()
{
#ifdef _DEBUG
	DrawFormatString(0, 215, 0xffffff, "EnemyHitPoint : %d", m_currentHP);
#endif // _DEBUG

	//UIの描画
	//HPの枠の描画
	//元画像の枠が5HP分しかないので
	//6HP以上の場合は1メモリを伸ばして枠を伸ばす
	//最初の枠の描画
	DrawRectRotaGraph(
		static_cast<int>(m_pos.x) - draw_fir_offset_x,
		static_cast<int>(m_pos.y),
		0,0,
		first_frame_width, frame_height,
		graph_size, 0.0,
		m_handles[static_cast<int>(HandleNomber::Frame)],
		true, false);

	//1メモリを伸ばす場所の描画
	for (int i = 0; i < m_maxHP - 1; ++i) {
		DrawRectRotaGraph(
			static_cast<int>(m_pos.x + first_frame_width + i * next_hp_offset),//X座標
			static_cast<int>(m_pos.y),//Y座標
			first_frame_width, 0,//切り取り開始位置
			one_hp_width, frame_height,//切り取りサイズ
			graph_size, 0.0,
			m_handles[static_cast<int>(HandleNomber::Frame)],
			true, false);
	}

	//最後の枠の描画
	const int firAndMidWidth = first_frame_width + (m_maxHP - 1) * one_hp_width;//最初と中間の枠の合計幅
	DrawRectRotaGraph(
		static_cast<int>( m_pos.x + firAndMidWidth) + draw_last_offset_x,//X座標
		static_cast<int>(m_pos.y),//Y座標
		last_frame_srcX, 0,//切り取り開始位置
		last_frame_width, frame_height,//切り取りサイズ
		graph_size, 0.0,//画像倍率と回転角度
		m_handles[static_cast<int>(HandleNomber::Frame)],
		true, false);

	//ハートの描画
	DrawRotaGraph(
		static_cast<int>(m_pos.x + 60),
		static_cast<int>(m_pos.y),
		graph_size, 0.0,
		m_handles[static_cast<int>(HandleNomber::Heart)],
		true, false);

	//HPバーの空の部分を先に描画しておいて
	//その上に現在のHPを描画する
	for (int i = 0; i < m_maxHP; ++i)
	{
		//空HPの描画
		DrawRotaGraph(
			static_cast<int>(m_pos.x + i * next_hp_offset - empty_hp_offset_x),
			static_cast<int>(m_pos.y),
			graph_size, 0.0,
			m_handles[static_cast<int>(HandleNomber::Empty)],
			true, false);
	}

	switch (m_currentHP)
	{
	case hp_1://HPが1の時
	case hp_2://HPが2の時
		for (int i = 0; i < m_currentHP; ++i)
		{
			//ピンチ時のHPの描画
			DrawRotaGraph(
				static_cast<int>(m_pos.x  + i * next_hp_offset + 60),
				static_cast<int>(m_pos.y ),
				graph_size, 0.0,
				m_handles[static_cast<int>(HandleNomber::Pinch)],
				true, false);
		}
		break;
	case hp_3://HPが3の時
	case hp_4://HPが4の時
	case hp_5://HPが5の時
	case hp_6://HPが6の時
	case hp_7://HPが7の時
	case hp_8://HPが8の時
	case hp_9://HPが9の時
	case hp_10://HPが10の時
		for (int i = 0; i < m_currentHP; ++i)
		{
			//ノーマルHP描画
			DrawRotaGraph(
				static_cast<int>(m_pos.x + i * next_hp_offset - pinch_hp_offset),
				static_cast<int>(m_pos.y),
				graph_size, 0.0,
				m_handles[static_cast<int>(HandleNomber::Normal)],
				true, false);
		}
		break;
	}
}
