#include "ChargeShotBoss.h"
#include "EnemyBullet.h"
#include <DxLib.h>
#include "Player.h"

namespace
{
	constexpr int size_width = 128;//幅
	constexpr int size_height = 128;//高さ

	const Vector2 first_pos = { 500.0f,500.0f };
	constexpr int attack_cooltime = 60;//攻撃のクールタイム
	constexpr float bullet_pos_offset = 10.0f;
}

ChargeShotBoss::ChargeShotBoss() :
	m_attackCooltime(0),
	m_isRight(true)
{
	m_pBullets.resize(5);
	for (auto& bullet : m_pBullets)
	{
		bullet = std::make_shared<EnemyBullet>();
	}
}

ChargeShotBoss::~ChargeShotBoss()
{
}

void ChargeShotBoss::Init()
{
	m_pos = first_pos;
	m_sizeWidth = size_width;
	m_sizeHeight = size_height;
	m_attackCooltime = attack_cooltime;

	for (auto& bullet : m_pBullets)
	{
		bullet->Init();
	}
}

void ChargeShotBoss::Update()
{
	//スクリュードライバーの中心座標を基準にする
	m_colRect.SetCenter(m_pos.x, m_pos.y, m_sizeWidth, m_sizeHeight);

	//攻撃のクールタイムを更新
	m_attackCooltime--;
	//攻撃のクールタイムが0以下になったら攻撃
	if (m_attackCooltime <= 0)
	{
		Attack();
		//クールタイムをリセット
		m_attackCooltime = attack_cooltime;
	}
	//弾の動きを更新
	for (auto& bullet : m_pBullets)
	{
		bullet->Update();
	}
}

void ChargeShotBoss::Draw()
{
#if _DEBUG
	m_colRect.Draw(0xaaffff, false);
	DrawFormatString(0, 80, 0xffffff, "AttackCooltime:%d", m_attackCooltime);
#endif
	for (auto& bullet : m_pBullets)
	{
		bullet->Draw();
	}
}

void ChargeShotBoss::Attack()
{
	for (auto& bullet : m_pBullets)
	{	
		//弾を撃つ
		if (!bullet->GetIsAlive())
		{
			
			//プレイヤーの場所を取得して
			//弾の向きを決定する
			if (m_pPlayer->GetPos().x > m_pos.x)
			{
				bullet->SetDir({ 1.0f,0.0f });
				//弾の初期位置を設定
				bullet->SetPos({ m_pos.x + m_sizeWidth / 2, m_pos.y });
			}
			else
			{
				bullet->SetDir({ -1.0f,0.0f });
				//弾の初期位置を設定
				bullet->SetPos({ m_pos.x - m_sizeWidth / 2, m_pos.y });
			}
			bullet->SetIsAlive(true);
		}
	}
}