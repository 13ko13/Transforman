#include "EnemyBullet.h"
#include <DxLib.h>

constexpr int radius = 10;

EnemyBullet::EnemyBullet()
{

}

EnemyBullet::~EnemyBullet()
{

}

void EnemyBullet::Init()
{

}

void EnemyBullet::Update()
{

}

void EnemyBullet::Draw()
{
#if _DEBUG
	if (m_isAlive)
	{
		//“–‚½‚è”»’è‚ð•`‰æ‚·‚é
		DrawCircle(m_pos.x, m_pos.y, radius, GetColor(255, 0, 0), false, 1);
		DrawFormatString(0, 65, 0xffffff, L"EnemyBulletPos X : %f , Y : %f", m_pos.x, m_pos.y);
	}
#endif 
}
