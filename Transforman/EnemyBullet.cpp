#include "EnemyBullet.h"
#include <DxLib.h>
#include "GameConstants.h"
#include <cmath>
#include "Player.h"
#include "ChargeShotBoss.h"

namespace
{
	constexpr int radius = 10;
	constexpr float speed = 3.0f;
	constexpr int way_num = 5;
	constexpr float angle_30 = DX_PI_F / 6.0f;
	constexpr int bullet_num = 128;
}

EnemyBullet::EnemyBullet() 
{
	m_state = EnemyState::Normal;
}

EnemyBullet::~EnemyBullet()
{

}

void EnemyBullet::Init()
{
	m_dir = { 0.0f,0.0f };
}

void EnemyBullet::Update()
{
	//弾が存在している場合のみ更新
	if (m_isAlive)
	{
		//弾の移動処理
		Movement();
		//画面外に出てしまった場合は存在状態を
		//保持している変数にfalseを代入
		if (m_pos.y < 0 || m_pos.y > Graphic::screen_height ||
			m_pos.x < 0 || m_pos.x > Graphic::screen_width)
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
		DrawFormatString(0, 115, 0xffffff,"EnemyBulletPos X : %f , Y : %f", m_pos.x, m_pos.y);
		DrawFormatString(0, 130, 0xffffff, "ShotDir : %f , %f", m_dir.x, m_dir.y);
		DrawFormatString(0, 95, 0xffffff, "EnemyBulletAlive : %d", m_isAlive);
	}
#endif 
	
}

void EnemyBullet::Movement()
{
	//弾を移動させる。dirは常に上方向で長さ1なので、
	//正規化はいらない
	Vector2 shotVelocity = m_dir * speed;
	m_pos += shotVelocity;
}
