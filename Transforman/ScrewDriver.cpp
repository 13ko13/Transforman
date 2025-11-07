#include "ScrewDriver.h"
#include "EnemyBullet.h"
#include <DxLib.h>

namespace
{
	constexpr int size_width = 32;//幅
	constexpr int size_height = 32;//高さ

	const Vector2 first_pos = { 500.0f,500.0f };
	constexpr int attack_cooltime = 60;//攻撃のクールタイム
}

ScrewDriver::ScrewDriver() : 
	m_attackCooltime(0)
{
	m_pBullet = std::make_shared<EnemyBullet>();
}

ScrewDriver::~ScrewDriver()
{
}

void ScrewDriver::Init()
{
	m_pos = first_pos;
	m_sizeWidth = size_width;
	m_sizeHeight = size_height;
	m_attackCooltime = attack_cooltime;
}

void ScrewDriver::Update()
{
	//スクリュードライバーの中心座標を基準にする
	m_colRect.SetCenter(m_pos.x, m_pos.y, m_sizeWidth, m_sizeHeight);
	
	//攻撃のクールタイムを更新
	m_attackCooltime--;
	//攻撃のクールタイムが0以下になったら攻撃
	if( m_attackCooltime <= 0 )
	{
		Attack();
		//クールタイムをリセット
		m_attackCooltime = attack_cooltime;
	}
}

void ScrewDriver::Draw()
{
#if _DEBUG
	m_colRect.Draw(0xaaffff,false);
	DrawFormatString(0, 80, 0xffffff, L"AttackCooltime:%d", m_attackCooltime);
#endif
}

void ScrewDriver::Attack()
{
	//弾を撃つ
	if (!m_pBullet->GetIsAlive())
	{
		//弾が存在していない場合弾を発射する
		m_pBullet->SetPos({ m_pos.x, m_pos.y });
		m_pBullet->SetIsAlive(true);
	}
}