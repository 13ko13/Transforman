#include "ChargeShotBoss.h"
#include "EnemyBullet.h"
#include <DxLib.h>
#include "Player.h"
#include <cassert>
#include "Camera.h"

namespace
{
	constexpr int size_width = 128;//幅
	constexpr int size_height = 128;//高さ
	constexpr int graph_width = 48;	//画像1枚の幅
	constexpr int graph_height = 32;//画像1枚の高さ

	const Vector2 first_pos = { 500.0f,500.0f };
	constexpr int attack_cooltime = 60;//攻撃のクールタイム
	constexpr float bullet_pos_offset = 10.0f;
}

ChargeShotBoss::ChargeShotBoss() :
	m_attackCooltime(0),
	m_isRight(true)
{
	m_handle = LoadGraph("img/game/Enemy/chargeShot.png");
	assert(m_handle > -1);
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
}

void ChargeShotBoss::Update()
{

}

void ChargeShotBoss::Update(std::vector<std::shared_ptr<EnemyBullet>>& pBullets)
{
	//攻撃のクールタイムを更新
	m_attackCooltime--;
	//攻撃のクールタイムが0以下になったら攻撃 
	if (m_attackCooltime <= 0)
	{
		Attack(pBullets);
		//クールタイムをリセット
		m_attackCooltime = attack_cooltime;
	}
	//弾の動きを更新
	for (auto& bullet : pBullets)
	{
		bullet->Update();
	}
}

void ChargeShotBoss::Draw(Camera camera)
{
#if _DEBUG
	m_pColRect->Draw(0xaaffff, false, camera);
	DrawFormatString(0, 80, 0xffffff, "AttackCooltime:%d", m_attackCooltime);
#endif
}

void ChargeShotBoss::Attack()
{

}

void ChargeShotBoss::Attack(std::vector<std::shared_ptr<EnemyBullet>>& pBullets)
{
	for (auto& bullet : pBullets)
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
