#include "Bullet.h"
#include <DxLib.h>
#include "GameConstants.h"
#include "Player.h"

namespace 
{
	constexpr float speed = 5.0f;
	constexpr int radius = 10.0f;
}

Bullet::Bullet() :
	Object({ 0.0f,0.0f }, { 0.0f,0.0f }),
	m_dir({ 0.0f,0.0f }),
	m_isAlive(false),
	m_isRight(false)
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
		//’e‚ğˆÚ“®‚³‚¹‚éBdir‚Íí‚Éã•ûŒü‚Å’·‚³1‚È‚Ì‚ÅA
		//³‹K‰»‚Í‚¢‚ç‚È‚¢
		Vector2 shotVelocity = m_dir * speed;
		m_pos = m_pos + shotVelocity;

		//‰æ–ÊŠO‚Éo‚Ä‚µ‚Ü‚Á‚½ê‡‚Í‘¶İó‘Ô‚ğ
		//•Û‚µ‚Ä‚¢‚é•Ï”‚Éfalse‚ğ‘ã“ü
		if( m_pos.x < 0 || m_pos.x > Graphic::screen_width )
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
		//’e‚ğ•`‰æ‚·‚é
		DrawCircle(m_pos.x, m_pos.y, radius, GetColor(255, 0, 0), false, 1);
		DrawFormatString(0, 45, 0xffffff, L"Bullet Pos X:%f Y:%f", m_pos.x, m_pos.y);
#endif
	}
}
