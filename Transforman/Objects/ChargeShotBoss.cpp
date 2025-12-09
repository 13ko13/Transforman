#include "ChargeShotBoss.h"
#include "EnemyBullet.h"
#include <DxLib.h>
#include "Player.h"
#include <cassert>
#include "../Graphics/Camera.h"
#include "../General/GameConstants.h"

namespace
{
	constexpr float ground = Graphic::screen_height - 100;	//地面の高さ(仮)

	constexpr int size_width = 128;//幅
	constexpr int size_height = 128;//高さ
	constexpr int graph_width = 48;	//画像1枚の幅
	constexpr int graph_height = 32;//画像1枚の高さ

	const Vector2 first_pos = { 2380.0f,-32 };
	constexpr int attack_cooltime = 60;//攻撃のクールタイム
	constexpr int appear_time = 30;//出現からノーマルに遷移するまでの時間
	constexpr float bullet_pos_offset = 10.0f;
	constexpr float appear_gravity = 6.0f;//出現中の重力
	//アニメーション関連
	constexpr int graph_idx_idle = 0;//待機状態
	constexpr int graph_idx_appear = 0;//出現状態(画像がないので1アイドルと同じ状態)
	constexpr int graph_idx_rush = 0;//突進状態(画像がないので1アイドルと同じ状態)
	constexpr int graph_idx_shot = 1;//弾撃ち状態
	
	constexpr int anim_wait_frame = 8;//次のアニメーションまでの待機時間
	constexpr int anim_wait_rush = 3;//突進中のアニメーション待機時間
	constexpr int idle_anim_frame = 4;//待機状態のアニメーション枚数
	constexpr int appear_anim_frame = 4;//出現中のアニメーション枚数
	constexpr int rush_anim_frame = 4;//突進中のアニメーション枚数
	constexpr int shot_anim_frame = 10;//弾撃ちアニメーションの枚数
}

ChargeShotBoss::ChargeShotBoss(std::shared_ptr<Map> pMap) :
	EnemyBase(size_width, size_height, pMap),
	m_attackCoolTime(0)
{
	m_handle = LoadGraph("img/game/Enemy/chargeShot.png");
	assert(m_handle >= 0);

	m_pos = first_pos;
	m_attackCoolTime = attack_cooltime;
}

ChargeShotBoss::~ChargeShotBoss()
{
	DeleteGraph(m_handle);
}

void ChargeShotBoss::Init()
{

}

void ChargeShotBoss::Update(GameContext& ctx)
{
	m_animFrame++;

	//攻撃のクールタイムを更新
	m_attackCoolTime--;
	//攻撃のクールタイムが0以下になったら攻撃 
	if (m_attackCoolTime <= 0 && !m_isDead)
	{
		Attack(ctx.p_enemyBullets, ctx.player);
		//クールタイムをリセット
		m_attackCoolTime = attack_cooltime;
	}

	int animMax = 0;//アニメーション最大枚数

#ifdef _DEBUG
	//ボタンでステート切り替え
	if (ctx.input.IsTriggered("changeState(enemy)"))
	{
		m_state = State::Rush;
	}
#endif // DEBUG

	switch (m_state)
	{
	case State::Appear:
		animMax = appear_anim_frame;
		//生きているなら行動
		if (!m_isDead)
		{
			//ボス部屋到達後に何もいない→上から降ってくる
			//演出をやりたいのでマップチップの当たり判定は行わない
			//降下する時の重力を下げる
			//出現中タイム更新
			m_appearTime--;
			m_velocity.y = appear_gravity;
			m_pos.y += m_velocity.y;
			//効果から数秒経ったら状態をノーマルにする
			if (m_appearTime <= 0)
			{
				m_state = State::Idle;
				m_velocity.y = 0.0f;
			}
		}
		break;
	case State::Idle:
		animMax = idle_anim_frame;
		//生きているなら行動させる
		if (!m_isDead)
		{
			Rect chipRect;	//当たったマップチップの矩形
			HitMap(chipRect);//マップとの接地判定

			Charactor::Update(ctx);
		}
		break;
	case State::Rush:
		animMax = rush_anim_frame;
		//生きているなら行動させる
		if (!m_isDead)
		{
			Rect chipRect;	//当たったマップチップの矩形
			HitMap(chipRect);//マップとの接地判定

			Charactor::Update(ctx);
			//とりあえず動かす
			m_velocity.x = -5.0f;
		}
		break;
	case State::Shot:
		animMax = shot_anim_frame;
		break;
	}
	switch (m_state)
	{
	case State::Appear:
	case State::Idle:
	case State::Shot:
		//アニメーション更新
		//全枚数のアニメーションを終えたら
		//1枚目の画像に戻す
		if (m_animFrame >= animMax * anim_wait_frame)
		{
			m_animFrame = 0.0f;
		}
		break;
	case State::Rush:
		//突進中のみアニメーションを早くする
		if (m_animFrame >= animMax * anim_wait_rush)
		{
			m_animFrame = 0.0f;
		}
		break;
	}
}

void ChargeShotBoss::Draw(std::shared_ptr<Camera> pCamera)
{
	//アニメーションのフレーム数から表示したいコマ番号を計算で求める
	int animNo = m_animFrame / anim_wait_frame;

	//アニメーションの進行に合わせてグラフィックの横切り取り位置を変更する
	int srcX = animNo * graph_width;
	int srcY = 0;
	switch (m_state)
	{
	case State::Appear:
		srcY = graph_idx_appear;
		break;
	case State::Idle:
		srcY = graph_idx_idle;
		break;
	case State::Rush:
		srcY = graph_idx_rush;
		break;
	case State::Shot:
		srcY = graph_idx_shot;
		break;
	}

	//生きているなら描画
	if (!m_isDead)
	{
#if _DEBUG
		m_colRect.Draw(0xaaffff, false, pCamera);
		DrawFormatString(0, 80, 0xffffff, "AttackCooltime:%d", m_attackCoolTime);
		DrawFormatString(0, 290, 0xffffff, "ChargeBossPosY:%f", m_pos.y);
		DrawFormatString(0, 305, 0xffffff, "ChargeBossPosVelocityY:%f", m_velocity.y);
#endif
		//キャラクターを表示
		DrawRectRotaGraph(
			m_pos.x + pCamera->GetDrawOffset().x,
			m_pos.y + pCamera->GetDrawOffset().y,
			srcX, srcY,
			graph_width,graph_height,
			4.0, 0.0,
			m_handle, true, !m_isRight);
	}
}

void ChargeShotBoss::Attack()
{

}

void ChargeShotBoss::Attack(std::vector<std::shared_ptr<EnemyBullet>>& pBullets,
	std::shared_ptr<Player> pPlayer)
{
	for (auto& bullet : pBullets)
	{
		//弾を撃つ
		if (!bullet->GetIsAlive())
		{
			//プレイヤーの場所を取得して
			//弾の向きを決定する
			if (pPlayer->GetPos().x > m_pos.x)
			{
				bullet->SetDir({ 1.0f,0.0f });
				//弾の初期位置を設定
				bullet->SetPos({ m_pos.x + size_width / 2, m_pos.y });
			}
			else
			{
				bullet->SetDir({ -1.0f,0.0f });
				//弾の初期位置を設定
				bullet->SetPos({ m_pos.x - size_height / 2, m_pos.y });
			}
			bullet->SetIsAlive(true);
		}
	}
}

void ChargeShotBoss::OnArrive()
{
	//プレイヤーが到着したときのボスの処理
	//上から出現させてボスっぽくする
	m_pos = first_pos;
	m_appearTime = appear_time;
	m_state = State::Appear;
}
