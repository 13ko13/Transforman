#include "PlayerBullet.h"
#include <DxLib.h>
#include "../General/GameConstants.h"
#include "../Graphics/Camera.h"
#include "../Collider/Circle.h"
#include "EnemyBase.h"

namespace 
{
	constexpr float speed = 7.0f;
	constexpr float normal_shot_radius = 15.0f;
	constexpr float charge_shot_radius = 25.0f;

	//Fire
	constexpr int fire_width = 150;
	constexpr int fire_height = 30;
	constexpr float flame_life_time = 30.0f;//炎の残る時間
}

PlayerBullet::PlayerBullet() :
	m_isRight(false),
	m_flameLifeTime(0.0f)
{
	m_bulletType = BulletType::Normal;
	m_circle.SetPos(m_pos);
	m_circle.SetRadius(normal_shot_radius);
	//左上を基準に当たり判定を設定
	m_rect.SetLT(
		m_pos.x ,m_pos.y ,
		fire_width, fire_height);
}

PlayerBullet::~PlayerBullet()
{

}

void PlayerBullet::Init()
{
		
}

void PlayerBullet::Update(GameContext& ctx)
{
	

	switch (m_bulletType)
	{
	case BulletType::Normal:
		m_circle.SetRadius(normal_shot_radius);

		if (m_isAlive)
		{
			if (m_isRight)
			{
				m_dir = { 1.0f, 0.0f };
			}
			else
			{
				m_dir = { -1.0f, 0.0f };
			}
			m_circle.SetPos(m_pos);

			//弾を移動させる。dirは
			//常に上方向で長さ1なので、
			//正規化はいらない
			Vector2 shotVelocity = m_dir * speed;
			m_pos = m_pos + shotVelocity;

			//画面外に出てしまった場合は存在状態を
			//保持している変数にfalseを代入
			if (m_pos.x < 0 || m_pos.x > Graphic::screen_width)
			{
				m_isAlive = false;
			}
		}
		break;
	case BulletType::Charge:
		m_circle.SetRadius(charge_shot_radius);

		if (m_isAlive)
		{
			if (m_isRight)
			{
				m_dir = { 1.0f, 0.0f };
			}
			else
			{
				m_dir = { -1.0f, 0.0f };
			}

			m_circle.SetPos(m_pos);

			//弾を移動させる。dirは常に上方向で長さ1なので、
			//正規化はいらない
			Vector2 shotVelocity = m_dir * speed;
			m_pos = m_pos + shotVelocity;

			//画面外に出てしまった場合は存在状態を
			//保持している変数にfalseを代入
			if (m_pos.x < 0 || m_pos.x > Graphic::screen_width)
			{
				m_isAlive = false;
			}
		}
		break;
	case BulletType::Fire:
		m_flameLifeTime--;

		//左上を基準に当たり判定を設定
		//右を向いているときは自分の右側
		//左を向いているときは自分の左側に
		//火炎放射が出るようにする
		if (m_isRight)
		{
			m_rect.SetLT(
				m_pos.x,
				m_pos.y,
				fire_width, fire_height);
		}
		else
		{
			m_rect.SetLT(
				m_pos.x,
				m_pos.y,
				-fire_width, fire_height);
		}

		//炎の残り火時間が0以下になったら消えるようにする
		if (m_flameLifeTime <= 0)
		{
			m_isAlive = false;
		}
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
			m_circle.Draw(camera);

			DrawFormatString(
				0, 45, 0xffffff,
				"PlayerBulletPos X:%f , Y:%f",
				m_pos.x, m_pos.y);
#endif
			break;

		case BulletType::Charge:
#if _DEBUG
			//当たり判定を描画する
			m_circle.Draw(camera);
			DrawFormatString(0, 45, 0xffffff, "PlayerBulletPos X:%f , Y:%f", m_pos.x, m_pos.y);
#endif
			break;

		case BulletType::Fire:
#if _DEBUG
			//当たり判定を描画する
			m_rect.Draw(0xffffff, false, camera);
			DrawFormatString(0, 270, 0xffffff, "FlameLifeTime : %f", m_flameLifeTime);
#endif
			break;
		}
	}
}

void PlayerBullet::OnFlame()
{
	//炎が消えるまでの時間をセットする
	m_flameLifeTime = flame_life_time;
}
