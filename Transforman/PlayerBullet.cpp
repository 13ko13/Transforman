#include "PlayerBullet.h"
#include <DxLib.h>
#include "GameConstants.h"

namespace 
{
	constexpr float speed = 7.0f;
	constexpr int normal_shot_radius = 15.0f;
	constexpr int charge_shot_radius = 25.0f;
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

	switch (m_bulletType)
	{
	case BulletType::Normal:
		break;
	case BulletType::Charge:
		break;
	}
}

void PlayerBullet::Draw()
{
	if (m_isAlive)
	{
		switch (m_bulletType)
		{
		case BulletType::Normal:
#if _DEBUG
			//“–‚½‚è”»’è‚ğ•`‰æ‚·‚é
			DrawCircle(m_pos.x, m_pos.y, normal_shot_radius, GetColor(255, 0, 0), false, 1);
			DrawFormatString(0, 45, 0xffffff, "PlayerBulletPos X:%f , Y:%f", m_pos.x, m_pos.y);
#endif
			break;

		case BulletType::Charge:
#if _DEBUG
			//“–‚½‚è”»’è‚ğ•`‰æ‚·‚é
			DrawCircle(m_pos.x, m_pos.y, charge_shot_radius, GetColor(255, 0, 0), false, 1);
			DrawFormatString(0, 45, 0xffffff, "PlayerBulletPos X:%f , Y:%f", m_pos.x, m_pos.y);
#endif
			break;
		}

	}
}
