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

	const Vector2 first_pos = { 500.0f,500.0f };
	constexpr int attack_cooltime = 60;//攻撃のクールタイム
	constexpr float bullet_pos_offset = 10.0f;
}

ChargeShotBoss::ChargeShotBoss() :
	m_attackCooltime(0)
{
	m_handle = LoadGraph("img/game/Enemy/chargeShot.png");
	assert(m_handle >= 0);

	m_pos = first_pos;
	m_attackCooltime = attack_cooltime;

	m_colRect.SetLT(
		m_pos.x - size_width / 2,
		m_pos.y - size_height / 2 ,
		size_width, size_height);
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
	//生きているなら行動させる
	if (!m_isDead)
	{
		Gravity();
		m_pos += m_velocity;

		m_colRect.SetLT(
			m_pos.x - size_width / 2,
			m_pos.y - size_height / 2,
			size_width, size_height);

		//仮の地面を設定
		if (m_pos.y >= ground)
		{
			m_pos.y = ground;
			m_isGround = true;
			m_velocity.y = 0.0f;
		}
		else
		{
			m_isGround = false;
		}

		//攻撃のクールタイムを更新
		m_attackCooltime--;
		//攻撃のクールタイムが0以下になったら攻撃 
		if (m_attackCooltime <= 0)
		{
			Attack(ctx.p_enemyBullets, ctx.player);
			//クールタイムをリセット
			m_attackCooltime = attack_cooltime;
		}
		//弾の動きを更新
		for (auto& bullet : ctx.p_enemyBullets)
		{
			bullet->Update(ctx);
		}
	}
}

void ChargeShotBoss::Draw(Camera camera)
{
	//生きているなら描画
	if (!m_isDead)
	{
#if _DEBUG
		m_colRect.Draw(0xaaffff, false, camera);
		DrawFormatString(0, 80, 0xffffff, "AttackCooltime:%d", m_attackCooltime);
#endif
		//キャラクターを表示
		DrawRectRotaGraph(
			m_pos.x + camera.GetDrawOffset().x,
			m_pos.y + camera.GetDrawOffset().y,
			0, 0, graph_width,
			graph_height,
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
