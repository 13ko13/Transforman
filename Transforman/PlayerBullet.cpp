#include "PlayerBullet.h"
#include <DxLib.h>
#include "GameConstants.h"
#include "Camera.h"
#include "Circle.h"
#include "EnemyBase.h"

namespace 
{
	constexpr float speed = 7.0f;
	constexpr float normal_shot_radius = 15.0f;
	constexpr float charge_shot_radius = 25.0f;
}

PlayerBullet::PlayerBullet() :
	m_isRight(false)
{
	m_bulletType = BulletType::Normal;
}

PlayerBullet::~PlayerBullet()
{

}

void PlayerBullet::Init()
{
}

void PlayerBullet::Update()
{
	if( m_isRight )
	{
		m_dir = { 1.0f, 0.0f };
	}
	else
	{
		m_dir = { -1.0f, 0.0f };
	}

	if (m_isAlive == true)
	{
		m_pCircle->SetPos(m_pos);

		//弾を移動させる。dirは常に上方向で長さ1なので、
		//正規化はいらない
		Vector2 shotVelocity = m_dir * speed;
		m_pos = m_pos + shotVelocity;

		if (m_pCircle->IsCollWithRect(m_pEnemy->GetColRect()))
		{
			m_isAlive = false;
		}

		//画面外に出てしまった場合は存在状態を
		//保持している変数にfalseを代入
		if( m_pos.x < 0 || m_pos.x > Graphic::screen_width )
		{
			m_isAlive = false;
		}
	}

	switch (m_bulletType)
	{
	case BulletType::Normal:
		break;
	case BulletType::Charge:
		break;
	}
}

void PlayerBullet::Draw(Camera camera)
{
	if (m_isAlive)
	{
		switch (m_bulletType)
		{
		case BulletType::Normal:
#if _DEBUG
			//当たり判定を描画する
			m_pCircle->SetRadius(normal_shot_radius);
			m_pCircle->Draw(camera);

			DrawFormatString(
				0, 45, 0xffffff,
				"PlayerBulletPos X:%f , Y:%f",
				m_pos.x, m_pos.y);
#endif
			break;

		case BulletType::Charge:
#if _DEBUG
			//当たり判定を描画する
			m_pCircle->SetRadius(charge_shot_radius);
			m_pCircle->Draw(camera);
			DrawFormatString(0, 45, 0xffffff, "PlayerBulletPos X:%f , Y:%f", m_pos.x, m_pos.y);
#endif
			break;
		}

	}
}
