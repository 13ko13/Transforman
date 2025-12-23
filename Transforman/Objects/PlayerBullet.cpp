#include "PlayerBullet.h"
#include <DxLib.h>
#include "../General/GameConstants.h"
#include "../Graphics/Camera.h"
#include "../Collider/Circle.h"
#include "EnemyBase.h"
#include "../Stages/Stage.h"
#include <cassert>

namespace 
{
	constexpr float speed = 7.0f;
	constexpr float normal_shot_radius = 15.0f;
	constexpr float charge_shot_radius = 25.0f;

	//アニメーション
	constexpr int anim_idx_y = 0;
	constexpr int max_normal_anim_num = 4;
	constexpr int one_anim_frame = 5;
	constexpr int graph_width = 16;
	constexpr int graph_height = 16;
	constexpr float draw_scale = 3.0f;

	//Fire
	constexpr int fire_width = 150;
	constexpr int fire_height = 30;
	constexpr float flame_life_time = 30.0f;//炎の残る時間
	
	constexpr int chip_size = 32;//マップチップのサイズ
}

PlayerBullet::PlayerBullet() :
	m_animFrame(0),
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
	//画像をロード
	m_handle = LoadGraph("img/game/bullet/player_bullet.png");
	assert(m_handle >= 0);
}

PlayerBullet::~PlayerBullet()
{

}

void PlayerBullet::Init()
{
	m_normalAnim.Init(m_handle, 0, { graph_width ,graph_height }, max_normal_anim_num, one_anim_frame,draw_scale, true);
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

			//ステージ外に出てしまった場合は存在状態を
			//保持している変数にfalseを代入
			const auto& mapSize = ctx.pStage->GetMapSize();
			if (m_pos.x < 0 - normal_shot_radius||
				m_pos.x > mapSize.w * chip_size + normal_shot_radius)
			{
				m_isAlive = false;
			}
			//アニメーションの更新
			m_normalAnim.Update();
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
			//ステージ外に出てしまった場合は存在状態を
			//保持している変数にfalseを代入
			const auto& mapSize = ctx.pStage->GetMapSize();
			if (m_pos.x < 0 - normal_shot_radius ||
				m_pos.x > mapSize.w * chip_size + normal_shot_radius)
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

void PlayerBullet::Draw(std::shared_ptr<Camera> pCamera)
{
	if (m_isAlive)
	{
		switch (m_bulletType)
		{
		case BulletType::Normal:
#if _DEBUG
			//当たり判定を描画する
			m_circle.Draw(pCamera);

			DrawFormatString(
				0, 45, 0xffffff,
				"PlayerBulletPos X:%f , Y:%f",
				m_pos.x, m_pos.y);
#endif
			//アニメーションのdraw
			m_normalAnim.Draw(
				{ m_pos.x + pCamera->GetDrawOffset().x,
				m_pos.y + pCamera->GetDrawOffset().y }, m_isRight);
			break;

		case BulletType::Charge:
#if _DEBUG
			//当たり判定を描画する
			m_circle.Draw(pCamera);
			DrawFormatString(0, 45, 0xffffff, "PlayerBulletPos X:%f , Y:%f", m_pos.x, m_pos.y);
#endif
			break;

		case BulletType::Fire:
#if _DEBUG
			//当たり判定を描画する
			m_rect.Draw(0xffffff, false, pCamera);
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
