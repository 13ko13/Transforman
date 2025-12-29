#include "ParryBoss.h"
#include <Dxlib.h>
#include "../Graphics/Camera.h"
#include <cassert>
#include "../Stages/Stage.h"
#include "../Graphics/Animation.h"
#include "Player.h"

namespace
{
	constexpr int size_width = 150;
	constexpr int size_height = 150;
	constexpr int graph_width = 80;	//画像1枚の幅
	constexpr int graph_height = 80;//画像1枚の高さ

	//初期位置
	const Vector2 first_pos = { 500.0f, 500.0f };

	//アニメーション関連
	constexpr int max_anim_num = 9;//アニメーション枚数
	constexpr int one_anim_frame = 7;//1アニメーションあたりのフレーム数
	constexpr double draw_scale = 5.0f;
	constexpr float draw_offset_y = -40.0f;//キャラクターの描画オフセット
	constexpr float rotate_angle = 0.11f;//傾き角度
}

ParryBoss::ParryBoss(std::shared_ptr<Map> pMap) :
	EnemyBase(size_width, size_height, pMap),
	m_state(State::None)
{
	m_handle = LoadGraph("img/game/Enemy/parry_boss.png");
	assert(m_handle >= 0);

	m_pos = first_pos;
}

ParryBoss::~ParryBoss()
{

}

void ParryBoss::Init()
{
	m_idleAnim.Init(m_handle, 0, { graph_width,graph_height }, max_anim_num, one_anim_frame, draw_scale, true);
}

void ParryBoss::Update(GameContext& ctx)
{
#ifdef _DEBUG
	//ボタンでステート切り替え
	if (ctx.input.IsTriggered("changeState(enemy)"))
	{
		//次のステートへ
		m_state = static_cast<State>((static_cast<int>(m_state) + 1) % static_cast<int>(State::StateNum));
	}
#endif // DEBUG

	//常にプレイヤーの方向を見る
	const float playerPosX = ctx.pPlayer->GetPos().x;
	//プレイヤーが右にいるなら
	//突進中は突進している方向を向くようにする
	if (m_pos.x < playerPosX)
	{
		//右を見る
		m_isRight = true;
	}
	else//プレイヤーが左にいるなら
	{
		//左を見る
		m_isRight = false;
	}

	Charactor::Update(ctx);

	//マップとの当たり判定
	Rect chipRect;	//当たったマップチップの矩形
	HitMap(chipRect);//マップとの接地判定

	//状態ごとのアニメーション更新
	switch (m_state)
	{
		case State::None:

			break;
		case State::Appear:

			break;
		case State::Idle:
			//アニメーション更新
			m_idleAnim.Update();
			break;
	}
}

void ParryBoss::Draw(std::shared_ptr<Camera> pCamera)
{
	//アニメーション描画
	Vector2 drawPos = { m_pos.x, m_pos.y };//描画位置
	m_idleAnim.SetOffset({ 0.0f,draw_offset_y });//描画オフセットを設定
	drawPos += pCamera->GetDrawOffset();//カメラのオフセット分を足す
	//プレイヤーの方向に応じて少し傾けて描画
	if(m_isRight)
	{
		m_idleAnim.SetRotate(rotate_angle);//少し傾ける
	}
	else
	{
		m_idleAnim.SetRotate(-rotate_angle);//少し傾ける
	}
	m_idleAnim.Draw(drawPos, !m_isRight);

	//デバッグ用当たり判定表示
#ifdef _DEBUG
	Charactor::Draw(pCamera);
#endif // DEBUG
}

void ParryBoss::OnArrive()
{

}

void ParryBoss::Attack()
{
}
