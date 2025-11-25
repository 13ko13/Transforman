#include "PlayerBullet.h"
#include <DxLib.h>
#include "GameConstants.h"
#include "Camera.h"
#include "Circle.h"
#include "EnemyBase.h"

namespace 
{
	//普通の弾
	constexpr float speed = 7.0f;
	constexpr float normal_shot_radius = 15.0f;
	constexpr float charge_shot_radius = 25.0f;

	//火炎放射
	constexpr int fire_width = 20;//炎の横のサイズ
	constexpr int fire_height = 1;//炎の縦のサイズ
}

PlayerBullet::PlayerBullet() :
	m_isRight(false)
{
	m_bulletType = BulletType::Normal;
	m_circle.SetPos(m_pos);
	m_circle.SetRadius(normal_shot_radius);
	m_rect.SetLT(
				m_pos.x, m_pos.y,
				m_pos.x + fire_width,
				m_pos.y + fire_height);
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
		//弾の半径を設定
		m_circle.SetRadius(normal_shot_radius);
		//プレイヤーの向きに応じて弾の進む方向を変える
		if (m_isRight)
		{
			m_dir = { 1.0f, 0.0f };
		}
		else
		{
			m_dir = { -1.0f, 0.0f };
		}
		//弾が発射されていたら
		if (m_isAlive)
		{
			//ポジションを設定
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
	case BulletType::Charge:
		//弾の半径を設定
		m_circle.SetRadius(charge_shot_radius);
		//プレイヤーの向きに応じて弾の進む方向を変える
		if (m_isRight)
		{
			m_dir = { 1.0f, 0.0f };
		}
		else
		{
			m_dir = { -1.0f, 0.0f };
		}
		//弾が発射されていたら
		if (m_isAlive)
		{
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
		//プレイヤーの向きに応じて炎の出る方向を変える
		if (m_isRight)
		{
			m_dir = { 1.0f,0.0f };
		}
		else
		{
			m_dir = { -1.0f,0.0f };
		}

		//火炎放射が発動されたら
		if (m_isAlive)
		{
			//ポジションを設定
			m_rect.SetLT(
				m_pos.x, m_pos.y,
				m_pos.x + fire_width,
				m_pos.y + fire_height);
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
			//当たり判定を描画する
			m_rect.Draw(0xffffff,false,camera);
		}
	}
}
