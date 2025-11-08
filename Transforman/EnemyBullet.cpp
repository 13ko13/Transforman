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
		m_update = &EnemyBullet::DirUpUpdate;
		m_draw = &EnemyBullet::DirUpDraw;
		break;
	case Direction::Down:
		m_dir = { 0.0f, 1.0f };
		m_update = &EnemyBullet::DirDownUpdate;
		m_draw = &EnemyBullet::DirDownDraw;
		break;
	}
}

void EnemyBullet::Update()
{
	(this->*m_update)();
}

void EnemyBullet::Draw()
{
	(this->*m_draw)();
}

void EnemyBullet::DirUpUpdate()
{
	if (m_isAlive)
	{
		//弾を移動させる。dirは常に上方向で長さ1なので、
		//正規化はいらない
		Vector2 shotVelocity = m_dir * speed;
		m_pos += shotVelocity;
		//画面外に出てしまった場合は存在状態を
		//保持している変数にfalseを代入
		if (m_pos.y < 0 || m_pos.y > Graphic::screen_height ||
			m_pos.x < 0 || m_pos.x > Graphic::screen_width)
		{
			m_isAlive = false;
		}
	}
}

void EnemyBullet::DirDownUpdate()
{
	if (m_isAlive)
	{
		//弾を移動させる。dirは長さ1なので、
		//正規化はいらない
		Vector2 shotVelocity = m_dir * speed;
		m_pos += shotVelocity;
		//画面外に出てしまった場合は存在状態を
		//保持している変数にfalseを代入
		if (m_pos.y < 0 || m_pos.y > Graphic::screen_height ||
			m_pos.x < 0 || m_pos.x > Graphic::screen_width)
		{
			m_isAlive = false;
		}
	}
}

void EnemyBullet::DirUpDraw()
{
#if _DEBUG
	if (m_isAlive)
	{
		//当たり判定を描画する
		DrawCircle(m_pos.x, m_pos.y, radius, GetColor(255, 0, 0), false, 1);
		DrawFormatString(0, 65, 0xffffff, L"EnemyBulletPos X : %f , Y : %f", m_pos.x, m_pos.y);
	}
#endif 
	DrawFormatString(0, 95, 0xffffff, L"EnemyBulletAlive : %d", m_isAlive);
}

void EnemyBullet::DirDownDraw()
{
#if _DEBUG
	if (m_isAlive)
	{
		//当たり判定を描画する
		DrawCircle(m_pos.x, m_pos.y, radius, GetColor(255, 0, 0), false, 1);
		DrawFormatString(0, 65, 0xffffff, L"EnemyBulletPos X : %f , Y : %f", m_pos.x, m_pos.y);
	}
#endif 
	DrawFormatString(0, 95, 0xffffff, L"EnemyBulletAlive : %d", m_isAlive);
}
