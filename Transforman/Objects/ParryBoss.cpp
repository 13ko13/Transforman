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
	constexpr int fall_one_anim_frame = 4;//落下攻撃1アニメーションあたりのフレーム数
	constexpr double draw_scale = 5.0f;
	constexpr float draw_offset_y = -40.0f;//キャラクターの描画オフセット
	constexpr float rotate_angle = 0.11f;//傾き角度
	constexpr int parry_anim_num = 5;//パリィアニメーション枚数
	constexpr int parry_src_y = 3;//パリィアニメーションの切り取りY位置

	//攻撃関連
	constexpr float jump_move_speed = 10.0f;//ジャンプ中の移動速度
	constexpr int jump_duration = 120.0f;//ジャンプ継続フレーム数
	constexpr float jump_height = 300.0f;//ジャンプ高さ
	constexpr float target_offset_y = 20.0f;//ターゲットのYオフセット
}

ParryBoss::ParryBoss(std::shared_ptr<Map> pMap) :
	EnemyBase(size_width, size_height, pMap),
	m_state(State::None),
	m_moveCooldown(0),
	m_jumpFrame(0),
	m_playerPrevPos({ 0.0f,0.0f })
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
	m_jumpAnim.Init(m_handle, 2, { graph_width, graph_height }, 5, one_anim_frame, draw_scale, false);
	m_fallAttackAnim.Init(m_handle, 8, 2, { graph_width, graph_height }, 15, fall_one_anim_frame, draw_scale, false);
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
	case State::Jumping:
		m_jumpAnim.Update();
		JumpingUpdate(ctx);
		break;
	case State::FallAttack:
		m_fallAttackAnim.Update();
		FallAttackUpdate(ctx);
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
	case State::Jumping:
		JumpingDraw(pCamera);
		break;
	case State::FallAttack:
		FallAttackDraw(pCamera);
		break;
	}

	//デバッグ用当たり判定表示
#ifdef _DEBUG
	Charactor::Draw(pCamera);
	DrawFormatString(0, 450, 0xffffff, "ParryBossPosMoveCoolDown : %d",m_moveCooldown);
	DrawFormatString(0, 465, 0xffffff, "ParryBossVelocity.x : %f ,y : %f",m_velocity.x,m_velocity.y);
	DrawFormatString(0, 480, 0xffffff, "ParryBossPosX : %f ,Y : %f", m_pos.x, m_pos.y);
	DrawFormatString(0, 495, 0xffffff, "ParryBossState : %d", static_cast<int>(m_state));
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

void ParryBoss::JumpingDraw(std::shared_ptr<Camera> pCamera)
{
	//アニメーション描画
	Vector2 drawPos = { m_pos.x, m_pos.y };//描画位置
	m_jumpAnim.SetOffset({ 0.0f,draw_offset_y });//描画オフセットを設定
	drawPos += pCamera->GetDrawOffset();//カメラのオフセット分を足す
	//プレイヤーの方向に応じて少し傾けて描画
	if (m_isRight)
	{
		m_jumpAnim.SetRotate(rotate_angle);//少し傾ける
	}
	else
	{
		m_jumpAnim.SetRotate(-rotate_angle);//少し傾ける
	}
	m_jumpAnim.Draw(drawPos, !m_isRight);
}

void ParryBoss::FallAttackDraw(std::shared_ptr<Camera> pCamera)
{
	//アニメーション描画
	Vector2 drawPos = { m_pos.x, m_pos.y };//描画位置
	m_fallAttackAnim.SetOffset({ 0.0f,draw_offset_y });//描画オフセットを設定
	drawPos += pCamera->GetDrawOffset();//カメラのオフセット分を足す
	//プレイヤーの方向に応じて少し傾けて描画
	if (m_isRight)
	{
		m_fallAttackAnim.SetRotate(rotate_angle);//少し傾ける
	}
	else
	{
		m_fallAttackAnim.SetRotate(-rotate_angle);//少し傾ける
	}
	m_fallAttackAnim.Draw(drawPos, !m_isRight);
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
			m_state = State::Jumping;//ジャンプ状態に移行
			m_jumpFrame = jump_duration;//ジャンプ継続フレーム数をセット
			m_fallAttackAnim.Init(m_handle, 8, 2, { graph_width, graph_height }, 15, fall_one_anim_frame, draw_scale, false);
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
			m_parryAnim.Init(m_handle, 1, parry_src_y, { graph_width,graph_height }, parry_anim_num, one_anim_frame, draw_scale, false);
		}
	}
}

void ParryBoss::JumpingUpdate(GameContext& ctx)
{
	//ジャンプして、落下攻撃寸前まではプレイヤーの
	//位置の真上に移動する
	if (!m_isDead)
	{
		m_playerPrevPos = ctx.pPlayer->GetPos();
		--m_jumpFrame;
		//ジャンプから落下攻撃につなげるため
		//ジャンプ処理をここに書く
		//座標はプレイヤーの真上に移動
		//まずはジャンプさせる
		float targetY = m_playerPrevPos.y - jump_height;
		float disX = m_playerPrevPos.x - m_pos.x;
		float disY = targetY - m_pos.y;
		//その距離をジャンプ継続フレーム数で割って
		m_velocity.x = disX / jump_duration * jump_move_speed;
		m_velocity.y = disY / jump_duration * jump_move_speed;
		if (m_pos.y <= targetY + target_offset_y ||
			m_jumpFrame <= 0)
		{
			//ジャンプ継続フレーム数が0以下になったら
			//または目標地点に到達したら
			//落下攻撃状態に移行
			m_state = State::FallAttack;
			m_velocity.x = 0.0f;
			//アニメーションリセット
			m_jumpAnim.Init(m_handle, 2, { graph_width, graph_height }, 5, one_anim_frame, draw_scale, false);
		}
	}
}

void ParryBoss::FallAttackUpdate(GameContext& ctx)
{
}
