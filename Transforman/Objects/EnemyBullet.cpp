#include "EnemyBullet.h"
#include <DxLib.h>
#include "../General/GameConstants.h"
#include <cmath>
#include "Player.h"
#include "ChargeShotBoss.h"
#include "../Graphics/Camera.h"
#include "../Collider/Circle.h"
#include "../Stages/Stage.h"
#include <cassert>


namespace
{
	constexpr int radius = 20;
	constexpr float speed = 7.0f;
	constexpr int way_num = 5;
	constexpr float angle_30 = DX_PI_F / 6.0f;
	constexpr int bullet_num = 128;
	constexpr int chip_size = 32;//マップチップのサイズ
	constexpr int graph_width = 32;//画像の幅
	constexpr int graph_height = 32;//画像の高さ
	constexpr int src_idx_y = 1;//画像の縦の切り取り位置インデックス
	constexpr int ext_rate = 3;//弾のサイズ

	//アニメーション関連
	constexpr int anim_wait_frame = 6;//次のアニメーションに移る際の待機時間
	constexpr int bullet_anim_num = 4;//弾のアニメーション枚数
}

EnemyBullet::EnemyBullet()
{
	m_state = EnemyState::Normal;
	m_circle.SetPos(m_pos);
	m_circle.SetRadius(radius);
	m_handle = LoadGraph("img/game/Bullet/EnemyBullet.png");
	assert(m_handle >= 0);
}

EnemyBullet::~EnemyBullet()
{

}

void EnemyBullet::Init()
{
	m_dir = { 0.0f,0.0f };
}

void EnemyBullet::Update(GameContext& ctx)
{
	m_animFrame++;
	m_circle.SetRadius(radius);
	//弾が存在している場合のみ更新
	if (m_isAlive)
	{
		//当たり判定を中心に設定する
		m_circle.SetPos(m_pos);

		//弾の移動処理
		Movement();

		//画面外に出てしまった場合は存在状態を
		//保持している変数にfalseを代入
		const auto& mapSize = ctx.pStage->GetMapSize();
		const auto& boss_startPos = mapSize.w * chip_size - Graphic::screen_width - radius;
		if (m_pos.x < boss_startPos ||
			m_pos.x > mapSize.w * chip_size + radius)
		{
			m_isAlive = false;
		}
	}

	//現在のアニメーションのフレーム数が
	//現在のステートの描画枚数を超えたら
	//現在のアニメーションのフレーム数を0にする
	if (m_animFrame >= bullet_anim_num * anim_wait_frame)
	{
		m_animFrame = 0;
	}
}

void EnemyBullet::Draw(std::shared_ptr<Camera> pCamera)
{

	if (m_isAlive)
	{
		//アニメーションのフレーム数から表示したいコマ番号を計算で求める
		int animNo = m_animFrame / anim_wait_frame;

		//アニメーションの進行に合わせてグラフィックの横切り取り位置を変更する
		int srcX = animNo * graph_width;
		int srcY = src_idx_y * graph_height;

		DrawRectRotaGraph(static_cast<int>(m_pos.x + pCamera->GetDrawOffset().x ),
			static_cast<int>(m_pos.y + pCamera->GetDrawOffset().y),
			srcX, srcY,
			graph_width, graph_height,
			ext_rate, 0.0, m_handle, true);

#if _DEBUG
		m_circle.Draw(pCamera);
		DrawFormatString(0, 350, 0xffffff, "EnemyBulletPos X : %f , Y : %f", m_pos.x, m_pos.y);
		DrawFormatString(0, 130, 0xffffff, "ShotDir : %f , %f", m_dir.x, m_dir.y);
		DrawFormatString(0, 95, 0xffffff, "EnemyBulletAlive : %d", m_isAlive);
#endif 
	}
}

void EnemyBullet::Movement()
{
	//弾を移動させる。dirは常に上方向で長さ1なので、
	//正規化はいらない
	Vector2 shotVelocity = m_dir * speed;
	m_pos += shotVelocity;
}
