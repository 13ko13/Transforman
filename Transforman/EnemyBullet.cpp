#include "EnemyBullet.h"
#include <DxLib.h>
#include "GameConstants.h"

namespace
{
	constexpr int radius = 10;
	constexpr float speed = 3.0f;
}

EnemyBullet::EnemyBullet() :
	m_direction(Direction::Down)
{

}

EnemyBullet::~EnemyBullet()
{

}

void EnemyBullet::Init()
{
	switch (m_direction)
	{
	case Direction::Up:
		m_dir = { 0.0f, -1.0f };
		break;
	case Direction::Down:
		m_dir = { 0.0f, 1.0f };
		break;
	}
}

void EnemyBullet::Update()
{
	if (m_isAlive)
	{
		//弾を移動させる。dirは常に上方向で長さ1なので、
		//正規化はいらない
		Vector2 shotVelocity = m_dir * speed;
		m_pos += shotVelocity;
		//画面外に出てしまった場合は存在状態を
		//保持している変数にfalseを代入
		if( m_pos.y < 0 || m_pos.y > Graphic::screen_height || 
			m_pos.x > 0 || m_pos.x > Graphic::screen_width)
		{
			m_isAlive = false;
		}
	}
}

void EnemyBullet::Draw()
{
#if _DEBUG
	if (m_isAlive)
	{
		//当たり判定を描画する
		DrawCircle(m_pos.x, m_pos.y, radius, GetColor(255, 0, 0), false, 1);
		DrawFormatString(0, 65, 0xffffff, L"EnemyBulletPos X : %f , Y : %f", m_pos.x, m_pos.y);
	}
#endif 
}
