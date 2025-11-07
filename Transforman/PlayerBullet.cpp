#include "PlayerBullet.h"
#include <DxLib.h>
#include "GameConstants.h"

namespace 
{
	constexpr float speed = 5.0f;
	constexpr int radius = 10.0f;
}

PlayerBullet::PlayerBullet() :
	m_isRight(false)
{
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
		//弾を移動させる。dirは常に上方向で長さ1なので、
		//正規化はいらない
		Vector2 shotVelocity = m_dir * speed;
		m_pos = m_pos + shotVelocity;

		//画面外に出てしまった場合は存在状態を
		//保持している変数にfalseを代入
		if( m_pos.x < 0 || m_pos.x > Graphic::screen_width )
		{
			m_isAlive = false;
		}
	}
}

void PlayerBullet::Draw()
{
	if (m_isAlive == true)
	{
		

#if _DEBUG
		//当たり判定を描画する
		DrawCircle(m_pos.x, m_pos.y, radius, GetColor(255, 0, 0), false, 1);
		DrawFormatString(0, 45, 0xffffff, L"PlayerBulletPos X:%f , Y:%f", m_pos.x, m_pos.y);
#endif
	}
}
