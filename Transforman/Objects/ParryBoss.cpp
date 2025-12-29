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
	constexpr int idle_anim_num = 9;//アイドルアニメーション枚数
	constexpr int one_anim_frame = 7;//1アニメーションあたりのフレーム数
	constexpr double draw_scale = 5.0f;
	constexpr float draw_offset_y = -40.0f;//キャラクターの描画オフセット
	constexpr float rotate_angle = 0.11f;//傾き角度
	constexpr int parry_anim_num = 5;//パリィアニメーション枚数
	constexpr int parry_src_y = 3;//パリィアニメーションの切り取りY位置
}

ParryBoss::ParryBoss(std::shared_ptr<Map> pMap) :
	EnemyBase(size_width, size_height, pMap),
	m_state(State::None),
	m_moveCooldown(0)
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
	m_idleAnim.Init(m_handle, 0, { graph_width,graph_height }, idle_anim_num, one_anim_frame, draw_scale, true);
	m_parryAnim.Init(m_handle, parry_src_y, { graph_width,graph_height }, parry_anim_num, one_anim_frame, draw_scale, false);
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

	//行動クールタイム更新
	if (m_moveCooldown > 0)
	{
		m_moveCooldown--;
	}

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
		IdleUpdate(ctx);
		break;
	case State::Parry:
		m_parryAnim.Update();
		ParryUpdate(ctx);
		break;
	}
}

void ParryBoss::Draw(std::shared_ptr<Camera> pCamera)
{
	switch (m_state)
	{
	case State::Appear:
		break;
	case State::Idle:
		IdleDraw(pCamera);
		break;
	case State::Parry:
		ParryDraw(pCamera);
		break;
	}

	//デバッグ用当たり判定表示
#ifdef _DEBUG
	Charactor::Draw(pCamera);
	DrawFormatString(0, 450, 0xffffff, "ParryBossPosMoveCoolDown : %d",m_moveCooldown);
#endif // DEBUG
}

void ParryBoss::OnArrive()
{

}

void ParryBoss::Attack()
{

}

void ParryBoss::IdleDraw(std::shared_ptr<Camera> pCamera)
{
	//アニメーション描画
	Vector2 drawPos = { m_pos.x, m_pos.y };//描画位置
	m_idleAnim.SetOffset({ 0.0f,draw_offset_y });//描画オフセットを設定
	drawPos += pCamera->GetDrawOffset();//カメラのオフセット分を足す
	//プレイヤーの方向に応じて少し傾けて描画
	if (m_isRight)
	{
		m_idleAnim.SetRotate(rotate_angle);//少し傾ける
	}
	else
	{
		m_idleAnim.SetRotate(-rotate_angle);//少し傾ける
	}
	m_idleAnim.Draw(drawPos, !m_isRight);
}

void ParryBoss::ParryDraw(std::shared_ptr<Camera> pCamera)
{
	//アニメーション描画
	Vector2 drawPos = { m_pos.x, m_pos.y };//描画位置
	m_parryAnim.SetOffset({ 0.0f,draw_offset_y });//描画オフセットを設定
	drawPos += pCamera->GetDrawOffset();//カメラのオフセット分を足す
	//プレイヤーの方向に応じて少し傾けて描画
	if (m_isRight)
	{
		m_parryAnim.SetRotate(rotate_angle);//少し傾ける
	}
	else
	{
		m_parryAnim.SetRotate(-rotate_angle);//少し傾ける
	}
	m_parryAnim.Draw(drawPos, !m_isRight);
}

void ParryBoss::IdleUpdate(GameContext& ctx)
{
	if (!m_isDead)
	{
		if (m_moveCooldown <= 0)
		{
			//行動クールタイムが0以下なら
			//次の行動を決定する
			m_moveCooldown = 120;//クールタイムをリセット
			//次の行動を決定
			m_state = State::Parry;//とりあえずパリィにする
		}
	}
}

void ParryBoss::ParryUpdate(GameContext& ctx)
{
	if(!m_isDead)
	{
		//パリィアニメーションが最後まで行ったら
		if (m_parryAnim.GetIsEnd())
		{
			//状態をアイドルに戻す
			m_state = State::Idle;
			//アニメーションを最初に戻す
			m_parryAnim.Init(m_handle, parry_src_y, { graph_width,graph_height }, parry_anim_num, one_anim_frame, draw_scale, false);
		}
	}
}
