#include "ChargeShotBoss.h"
#include "EnemyBullet.h"
#include <DxLib.h>
#include "Player.h"
#include <cassert>
#include "../Graphics/Camera.h"
#include "../General/GameConstants.h"
#include "../Stages/Stage.h"

namespace
{
	constexpr int size_width = 144;//幅
	constexpr int size_height = 118;//高さ
	constexpr int graph_width = 48;	//画像1枚の幅
	constexpr int graph_height = 32;//画像1枚の高さ
	constexpr float draw_offset_y = 20.0f;//キャラクターの描画オフセット

	const Vector2 first_pos = { 2380.0f,-32.0f };
	constexpr int attack_cooltime = 60;//攻撃のクールタイム
	constexpr int appear_time = 60;//出現からノーマルに遷移するまでの時間
	constexpr float bullet_pos_offset = 10.0f;
	constexpr float appear_gravity = 6.0f;//出現中の重力
	constexpr float move_speed = 6.0f;//通常移動の速さ
	constexpr float prev_rush_speed = 0.001f;//突進準備中のほんの少し動く時のスピード
	constexpr int action_cooldown = 120;//次の行動までのフレーム数

	constexpr int prev_rush_frame = 120;//突進準備中の時間
	//アニメーション関連
	constexpr int graph_idx_idle = 0;//待機状態
	constexpr int graph_idx_appear = 0;//出現状態(画像がないので1アイドルと同じ状態)
	constexpr int graph_idx_rush = 0;//突進状態(画像がないので1アイドルと同じ状態)
	constexpr int graph_idx_shot = 1;//弾撃ち状態

	constexpr int anim_wait_frame = 10;//次のアニメーションまでの待機時間
	constexpr int anim_wait_prev_rush = 4;//突進準備中の次のアニメーションまでの待機時間
	constexpr int anim_wait_rush = 4;//突進中のアニメーション待機時間
	constexpr int idle_anim_frame = 4;//待機状態のアニメーション枚数

	constexpr int appear_anim_frame = 4;//出現中のアニメーション枚数
	constexpr int rush_anim_frame = 4;//突進中のアニメーション枚数
	constexpr int shot_anim_frame = 10;//弾撃ちアニメーションの枚数
	constexpr int chip_size = 32;		//マップチップのサイズ
}

ChargeShotBoss::ChargeShotBoss(std::shared_ptr<Map> pMap) :
	EnemyBase(size_width, size_height, pMap),
	m_prevRushTime(0),
	m_actionCooldown(0),
	m_isRushing(false),
	m_isStart(false)
{
	m_handle = LoadGraph("img/game/Enemy/chargeShot.png");
	assert(m_handle >= 0);

	m_pos = first_pos;
}

ChargeShotBoss::~ChargeShotBoss()
{
	DeleteGraph(m_handle);
}

void ChargeShotBoss::Init()
{

}

void ChargeShotBoss::Update(GameContext& ctx)
{
	m_animFrame++;

	//常にプレイヤーの方向を見る
	const float playerPosX = ctx.pPlayer->GetPos().x;
	//プレイヤーが右にいるなら
	//突進中は突進している方向を向くようにする
	if (!m_isRushing)
	{
		if (m_pos.x < playerPosX)
		{
			//右を見る
			m_isRight = true;
		}
		else//プレイヤーが左にいるなら
		{
			//左を見る
			m_isRight = false;
		}
	}

	int animMax = 0;//アニメーション最大枚数

#ifdef _DEBUG
	//ボタンでステート切り替え
	if (ctx.input.IsTriggered("changeState(enemy)"))
	{
		if (m_state == State::Idle)
		{
			m_state = State::PrevRush;
			m_prevRushTime = prev_rush_frame;
			return;
		}
		if (m_state == State::Rush)
		{
			m_state = State::Idle;
			return;
		}
	}
#endif // DEBUG

	//ステートごとの行動
	switch (m_state)
	{
	case State::None:
		if (!m_isDead)
		{
			Rect chipRect;	//当たったマップチップの矩形
			HitMap(chipRect);//マップとの接地判定
		}
		break;
	case State::Appear:
		animMax = appear_anim_frame;
		AppearUpdate();
		break;
	case State::Idle:
		animMax = idle_anim_frame;
		IdleUpdate(ctx);
		break;
	case State::PrevRush:
		animMax = rush_anim_frame;
		PrevRushUpdate(ctx);
		break;
	case State::Rush:
		animMax = rush_anim_frame;
		RushUpdate(ctx);
		break;
	case State::Shot:
		animMax = shot_anim_frame;
		ShotUpdate(ctx.pEnemyBullets, ctx.pPlayer);
		break;
	}

	if (m_state == State::Appear ||
		m_state == State::Idle ||
		m_state == State::Shot)
	{
		//アニメーション更新
		//全枚数のアニメーションを終えたら
		//1枚目の画像に戻す
		if (m_animFrame >= animMax * anim_wait_frame)
		{
			m_animFrame = 0;
		}
	}
	else if (m_state == State::PrevRush)
	{
		//Rush状態より早いアニメーションを行う
		if (m_animFrame >= animMax * anim_wait_prev_rush)
		{
			m_animFrame = 0;
		}
	}
	else if (m_state == State::Rush)
	{
		//突進中のみアニメーションを早くする
		if (m_animFrame >= animMax * anim_wait_rush)
		{
			m_animFrame = 0;
		}
	}
}

void ChargeShotBoss::Draw(std::shared_ptr<Camera> pCamera)
{
	//アニメーションのフレーム数から表示したいコマ番号を計算で求める
	int animNo = m_animFrame / anim_wait_frame;

	//アニメーションの進行に合わせてグラフィックの横切り取り位置を変更する
	int srcX = animNo * graph_width;
	int srcY = 0;
	switch (m_state)
	{
	case State::Appear:
		srcY = graph_idx_appear;
		break;
	case State::Idle:
		srcY = graph_idx_idle;
		break;
	case State::Rush:
		srcY = graph_idx_rush;
		break;
	case State::Shot:
		srcY = graph_idx_shot;
		break;
	}

	//生きているなら描画
	if (!m_isDead)
	{
#if _DEBUG
		m_colRect.Draw(0xaaffff, false, pCamera);
		DrawFormatString(0, 290, 0xffffff, "ChargeBossPosX:%f,Y:%f", m_pos.x,m_velocity.y);
		DrawFormatString(0, 305, 0xffffff, "ChargeBossPosVelocityX:%f,Y:%f", m_velocity.x,m_velocity.y);
		DrawFormatString(0, 320, 0xffffff, "ChargeBossState:%d", m_state);
		DrawFormatString(0, 370, 0xffffff, "PrevRushTime:%d", m_prevRushTime);

#endif
		//キャラクターを表示
		DrawRectRotaGraph(
			m_pos.x + pCamera->GetDrawOffset().x,
			m_pos.y + pCamera->GetDrawOffset().y - draw_offset_y,
			srcX, srcY,
			graph_width, graph_height,
			5.0, 0.0,
			m_handle, true, !m_isRight);
	}
}

void ChargeShotBoss::Attack()
{

}

void ChargeShotBoss::Attack(std::vector<std::shared_ptr<EnemyBullet>>& pBullets,
	std::shared_ptr<Player> pPlayer)
{
	//ランダムな確率でチャージショットと
	//突進を出してくるようにする
	const int stateShot = 0;
	const int stateRush = 1;
	const int random = GetRand(1);
	if (random == stateShot &&
		m_state == State::Idle && 
		m_actionCooldown <= 0)
	{
		m_state = State::Shot;
		m_actionCooldown = action_cooldown;
	}
	else if (random == stateRush &&
		m_state == State::Idle &&
		m_actionCooldown <= 0)
	{
		m_state = State::PrevRush;
		m_actionCooldown = action_cooldown;
		m_prevRushTime = prev_rush_frame;
	}
}

void ChargeShotBoss::OnArrive()
{
	//プレイヤーが到着したときのボスの処理
	//上から出現させてボスっぽくする
	m_pos = first_pos;
	m_appearTime = appear_time;
	m_state = State::Appear;
}

void ChargeShotBoss::ShotUpdate(std::vector<std::shared_ptr<EnemyBullet>>& pBullets,
	std::shared_ptr<Player> pPlayer)
{
	for (auto& bullet : pBullets)
	{
		//弾を撃つ
		if (!bullet->GetIsAlive())
		{
			//プレイヤーの場所を取得して
			//弾の向きを決定する
			if (pPlayer->GetPos().x > m_pos.x)
			{
				bullet->SetDir({ 1.0f,0.0f });
				//弾の初期位置を設定
				bullet->SetPos({ m_pos.x + size_width / 2, m_pos.y });
			}
			else
			{
				bullet->SetDir({ -1.0f,0.0f });
				//弾の初期位置を設定
				bullet->SetPos({ m_pos.x - size_width / 2, m_pos.y });
			}
			bullet->SetIsAlive(true);
			//弾を撃ったので状態をアイドルに戻してbreak
			m_state = State::Idle;
			break;
		}
	}
}

void ChargeShotBoss::RushUpdate(GameContext& ctx)
{
	int stageEnd = ctx.pStage->GetMapSize().w * chip_size;//ステージの終わり
	//生きているなら行動させる
	if (!m_isDead)
	{
		Rect chipRect;	//当たったマップチップの矩形
		HitMap(chipRect);//マップとの接地判定

		Charactor::Update(ctx);

		bool isColWall = m_pos.x < stageEnd - Graphic::screen_width + size_width / 2 ||
			m_pos.x >= stageEnd - chip_size * 2 - size_width / 2;//ボス部屋の端の壁に当たったかどうか
		if (!isColWall && !m_isRushing)
		{
			Vector2 dir = { 0.0f,0.0f };
			//右を向いているなら右方向を持つ
			if (m_isRight)
			{
				dir.x = 1.0f;
			}
			else//左を向いているなら左方向を持つ
			{
				dir.x = -1.0f;
			}
			m_isRushing = true;
			m_velocity += dir.Normalized() * move_speed;
		}

		//ボスが壁がない左端をすり抜けないように押し戻す
		if (m_pos.x < stageEnd - Graphic::screen_width + size_width / 2)
		{
			m_pos.x = stageEnd - Graphic::screen_width + size_width / 2;
			//壁にぶつかった判定で、velを0にする
			m_velocity.x = 0.0f;
		}

		if (isColWall)
		{
			//ステートをアイドルに戻す
			m_state = State::Idle;
			m_isRushing = false;
			ctx.pCamera->OnImpact();
		}
	}
}

void ChargeShotBoss::PrevRushUpdate(GameContext& ctx)
{
	//生きているなら行動させる
	if (!m_isDead)
	{
		m_prevRushTime--;
		//壁にぶつかった瞬間が取れず、条件文的に壁より左にいれば
		//常にカメラが揺れてしまうので、突進準備状態を作って
		//準備中なら、という条件を追加する
		Rect chipRect;	//当たったマップチップの矩形
		HitMap(chipRect);//マップとの接地判定
		Charactor::Update(ctx);

		//二回連続で突進が行われる際に
		//ほんの少しだけ移動させて壁との当たり判定が
		//常に行われないようにする
		Vector2 dir = { 0.0f,0.0f };
		//右を向いているなら右方向を持つ
		if (m_isRight)
		{
			dir.x = 1.0f;
		}
		else//左を向いているなら左方向を持つ
		{
			dir.x = -1.0f;
		}
		m_velocity += dir.Normalized() * prev_rush_speed;

		if (m_prevRushTime < 0)
		{
			m_velocity.x = 0.0f;
			m_state = State::Rush;
		}
	}
}

void ChargeShotBoss::AppearUpdate()
{
	//ボス部屋到達後に何もいない→上から降ってくる
	//演出をやりたいのでマップチップの当たり判定は行わない
	//降下する時の重力を下げる
	//出現中タイム更新
	m_appearTime--;
	m_velocity.y = appear_gravity;
	m_pos.y += m_velocity.y;
	//降下から数秒経ったら状態をノーマルにする
	if (m_appearTime <= 0)
	{
		m_state = State::Idle;
		m_velocity.y = 0.0f;
		m_isStart = true;
	}
}

void ChargeShotBoss::IdleUpdate(GameContext& ctx)
{
	//生きているなら行動させる
	if (!m_isDead)
	{
		m_actionCooldown--;
		Rect chipRect;	//当たったマップチップの矩形
		HitMap(chipRect);//マップとの接地判定

		Charactor::Update(ctx);

		//ランダムな攻撃方法をとる
		Attack(ctx.pEnemyBullets, ctx.pPlayer);
	}
}
