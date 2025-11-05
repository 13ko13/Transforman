#include "Bullet.h"
#include <DxLib.h>
#include "GameConstants.h"
#include "Player.h"

constexpr float speed = 3.0f;
constexpr int radius = 3.0f;

Bullet::Bullet() :
	Object({ 0.0f,0.0f }, { 0.0f,0.0f }),
	m_dir({ 0.0f,0.0f }),
	m_isAlive(false)
{
	m_pPlayer = std::make_shared<Player>();
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
}

void Bullet::Update()
{
	if (m_pPlayer->GetIsRight())
	{
		//プレイヤーが右を向いている場合
		m_dir = { 1.0f,0.0f };
	}
	else
	{
		//プレイヤーが左を向いている場合
		m_dir = { -1.0f ,0.0f };
	}

	if (m_isAlive == true)
	{
		//弾を移動させる。dirは常に上方向で長さ1なので、
		//正規化はいらない
		Vector2 shotVelocity = m_dir * speed;
		m_pos = m_pos + shotVelocity;

		//画面外に出てしまった場合は存在状態を
		//保持している変数にfalseを代入
		if (m_pos.y < Graphic::screen_height)
		{
			m_isAlive = false;
		}
	}
}

void Bullet::Draw()
{
	if (m_isAlive == true)
	{
#if _DEBUG
		//弾を描画する
		DrawCircle(m_pos.x, m_pos.y, radius, GetColor(255, 0, 0), false, 1);
#endif
	}
}
