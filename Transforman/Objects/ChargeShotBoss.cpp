#include "ChargeShotBoss.h"
#include "EnemyBullet.h"
#include <DxLib.h>
#include "Player.h"
#include <cassert>
#include "../Graphics/Camera.h"
#include "../General/GameConstants.h"
#include "../EffectFactory.h"
#include "../Effect.h"
#include "../Stages/Stage.h"

namespace
{
	constexpr int size_width = 144;//幅
	constexpr int size_height = 118;//高さ
	constexpr int graph_width = 48;	//画像1枚の幅
	constexpr int graph_height = 32;//画像1枚の高さ
	constexpr float draw_offset_y = 20.0f;//キャラクターの描画オフセット
	constexpr float p_draw_scale = 5.0f;

	const Vector2 first_pos = { 2380.0f,-32.0f };
	constexpr int attack_cooltime = 60;//攻撃のクールタイム
	constexpr int appear_time = 60;//出現からノーマルに遷移するまでの時間
	constexpr float bullet_pos_offset = 10.0f;
	constexpr float appear_gravity = 6.0f;//出現中の重力
	constexpr float move_speed = 12.0f;//突進の速さ
	constexpr float prev_rush_speed = 0.001f;//突進準備中のほんの少し動く時のスピード
	constexpr int action_cooldown = 70;//次の行動までのフレーム数

	constexpr int prev_rush_frame = 60;//突進準備中の時間
	//アニメーション関連
	constexpr int graph_idx_idle = 0;//待機状態
	constexpr int graph_idx_appear = 0;//出現状態(画像がないので1アイドルと同じ状態)
	constexpr int graph_idx_rush = 0;//突進状態(画像がないので1アイドルと同じ状態)
	constexpr int graph_idx_shot = 1;//弾撃ち状態

	constexpr int anim_wait_frame = 10;//次のアニメーションまでの待機時間
	constexpr int anim_wait_shot = 11;//ショット中の次のアニメーションまでの待機時間
	constexpr int anim_wait_prev_rush = 4;//突進準備中の次のアニメーションまでの待機時間
	constexpr int anim_wait_rush = 4;//突進中のアニメーション待機時間

	constexpr int idle_anim_frame = 4;//待機状態のアニメーション枚数
	constexpr int appear_anim_frame = 4;//出現中のアニメーション枚数
	constexpr int rush_anim_frame = 4;//突進中のアニメーション枚数
	constexpr int shot_anim_frame = 10;//弾撃ちアニメーションの枚数
	constexpr int chip_size = 32;		//マップチップのサイズ

	constexpr int max_hitpoint = 30;//ボスの最大体力

	constexpr int shake_power = 7;//地面に着地したときのカメラの揺れ力

	//エフェクトを出す指定位置
	constexpr float rush_effect_offset_y = 200.0f;

	//チャージショットを受けたときのダメージ
	constexpr int hit_chargeshot_damage = 3;
	constexpr int hit_normalshot_damage = 1;

	constexpr int hit_color_red = 255;//攻撃を受けたときの赤の度合い
	constexpr int hit_color_green = 100;//攻撃を受けたときの緑の度合い
	constexpr int hit_color_blue = 100;//攻撃を受けたときの青の度合い

	constexpr int death_effect_pos_y = 80;//死亡エフェクトを出すときの高さ
}

ChargeShotBoss::ChargeShotBoss(std::shared_ptr<Map> pMap, std::shared_ptr<EffectFactory> effectfactory) :
	EnemyBase(size_width, size_height, pMap, effectfactory),
	m_prevRushTime(0),
	m_actionCooldown(0),
	m_isRushing(false),
	m_isStart(false),
	m_GroundNum(0)
{
	m_handle = LoadGraph("img/game/Enemy/chargeshot_boss.png");
	assert(m_handle >= 0);

	m_pos = first_pos;
	m_state = State::None;
	//体力設定
	m_hitPoint = max_hitpoint;
}

ChargeShotBoss::~ChargeShotBoss()
{
	DeleteGraph(m_handle);
}

void ChargeShotBoss::Init()
{
	const Vector2 frameSize = { graph_width ,graph_height };
	m_idleAnim.Init(m_handle, 0, frameSize, idle_anim_frame, anim_wait_frame, p_draw_scale, true);
	m_prevRushAnim.Init(m_handle, 0, frameSize, rush_anim_frame, anim_wait_prev_rush, p_draw_scale, true);
	m_rushAnim.Init(m_handle, 0, frameSize, rush_anim_frame, anim_wait_rush, p_draw_scale, true);
	m_shotAnim.Init(m_handle, 1, frameSize, shot_anim_frame, anim_wait_shot, p_draw_scale, false);
}

void ChargeShotBoss::Update(GameContext& ctx)
{
	//HPが0になったら死亡フラグを立てる
	if (m_hitPoint <= 0)
	{
		m_isDead = true;
	}

	m_animFrame++;
	//地面についている間は地面についた回数をカウント
	if (m_isGround)
	{
		m_GroundNum++;
	}
	//一番最初に地面についた瞬間のみカメラを揺らす
	if (m_GroundNum == 1)
	{
		ctx.pCamera->OnImpact(shake_power);
	}

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
			//押し戻しはしているが地面についていない判定にする(ごり押し)
			m_isGround = false;
		}
		break;
	case State::Appear:
		AppearUpdate();
		break;
	case State::Idle:
		IdleUpdate(ctx);
		break;
	case State::PrevRush:
		PrevRushUpdate(ctx);
		break;
	case State::Rush:
		RushUpdate(ctx);
		break;
	case State::Shot:
		ShotUpdate(ctx.pEnemyBullets, ctx.pPlayer);
		break;
	}

	if (m_state == State::Appear ||
		m_state == State::Idle)
	{
		//アニメーション更新
		//全枚数のアニメーションを終えたら
		//1枚目の画像に戻す
		m_idleAnim.Update();
	}
	else if (m_state == State::PrevRush)
	{
		//Rush状態より早いアニメーションを行う
		m_prevRushAnim.Update();
	}
	else if (m_state == State::Rush)
	{
		//突進中のみアニメーションを早くする
		m_rushAnim.Update();
	}
	else if (m_state == State::Shot)
	{
		//ショットアニメーション更新
		m_shotAnim.Update();
	}
}

void ChargeShotBoss::Draw(std::shared_ptr<Camera> pCamera)
{
	//生きているなら描画
	if (!m_isDead)
	{
#if _DEBUG
		Charactor::Draw(pCamera);
		DrawFormatString(0, 290, 0xffffff, "ChargeBossPosX:%f,Y:%f", m_pos.x, m_velocity.y);
		DrawFormatString(0, 305, 0xffffff, "ChargeBossPosVelocityX:%f,Y:%f", m_velocity.x, m_velocity.y);
		DrawFormatString(0, 320, 0xffffff, "ChargeBossState:%d", m_state);
		DrawFormatString(0, 370, 0xffffff, "PrevRushTime:%d", m_prevRushTime);
		DrawFormatString(0, 430, 0xffffff, "ChargeBossIsGround:%d", m_isGround);
		DrawFormatString(0, 445, 0xffffff, "ChargeBossHP:%d", m_hitPoint);

#endif

		m_idleAnim.SetOffset({ 0,-draw_offset_y });
		m_rushAnim.SetOffset({ 0,-draw_offset_y });
		m_prevRushAnim.SetOffset({ 0,-draw_offset_y });
		m_shotAnim.SetOffset({ 0,-draw_offset_y });

		//被ダメージ時に赤くする
		if (m_isDamage)
		{
			SetDrawBright(hit_color_red, hit_color_green, hit_color_blue);
		}

		Vector2 drawPos = m_pos + pCamera->GetDrawOffset();
		//アニメーションの描画
		switch (m_state)
		{
		case State::Appear:
			m_idleAnim.Draw(drawPos, !m_isRight);
			break;
		case State::Idle:
			m_idleAnim.Draw(drawPos, !m_isRight);
			break;
		case State::Rush:
			m_rushAnim.Draw(drawPos, !m_isRight);
			break;
		case State::PrevRush:
			m_prevRushAnim.Draw(drawPos, !m_isRight);
			break;
		case State::Shot:
			m_shotAnim.Draw(drawPos, !m_isRight);
			break;
		}

		//描画後に明るさを元に戻す
		SetDrawBright(255, 255, 255);
	}
}

void ChargeShotBoss::Attack()
{

}

void ChargeShotBoss::Attack(std::vector<std::shared_ptr<EnemyBullet>>& pBullets,
	std::shared_ptr<Player> pPlayer)
{
	//地面についていないときは行動しない
	if (!m_isGround) return;

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

		//ショットアニメーションを最初から再生する
		m_shotAnim.SetFirst();
		return;
	}
	else if (random == stateRush &&
		m_state == State::Idle &&
		m_actionCooldown <= 0)
	{
		m_state = State::PrevRush;
		m_actionCooldown = action_cooldown;
		m_prevRushTime = prev_rush_frame;
		return;
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

void ChargeShotBoss::OnDamage(bool isChargeShot)
{
	if (isChargeShot)
	{
		if (m_hitPoint < 0) return;//死んでるなら何もしない

		//チャージショットを食らった場合3ダメージ
		m_hitPoint -= hit_chargeshot_damage;

		//HPが0になったら死亡時処理を呼ぶ
		if (m_hitPoint <= 0)
		{
			OnDead();
		}

	}
	else
	{
		if (m_hitPoint < 0) return;//死んでるなら何もしない
		//通常ショットなら1ダメージ
		m_hitPoint -= hit_normalshot_damage;
		//HPが0になったら死亡時処理を呼ぶ
		if (m_hitPoint <= 0)
		{
			OnDead();
		}
	}
}

void ChargeShotBoss::OnDead()
{
	//ボスが死んだのでエフェクトも削除する
	if (auto rushEffect = m_rushEffect.lock())
	{
		rushEffect->Kill();
	}

	//死亡エフェクトを生成
	m_pEffectFactory->Create(
		{ m_pos.x, m_pos.y - death_effect_pos_y },
		EffectType::enemyDeath,
		DeathCharactor::Enemy
	);
}

void ChargeShotBoss::ShotUpdate(std::vector<std::shared_ptr<EnemyBullet>>& pBullets,
	std::shared_ptr<Player> pPlayer)
{
	//アニメーションの発射フレームでのみ弾を打つ
	const int fireFrameIdx = 6;

	//現在のアニメーションのフレーム数を取得
	int currentFrame = m_shotAnim.GetNowAnimNum();

	//発射フレームに達していなければ何もしない
	if (currentFrame < fireFrameIdx) return;
	//弾を撃つ処理
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
			bullet->OnShot();
			//弾を撃ったので状態をアイドルに戻してbreak
			m_state = State::Idle;
			break;
		}
	}

	//アニメーションが最後まで行ったら
	//状態をアイドルに戻す
	if (m_shotAnim.GetIsEnd())
	{
		m_state = State::Idle;
	}
}

void ChargeShotBoss::RushUpdate(GameContext& ctx)
{
	int stageEnd = ctx.pStage->GetMapSize().w * chip_size;//ステージの終わり
	//生きているなら行動させる
	if (!m_isDead)
	{
		Charactor::Update(ctx);

		Rect chipRect;	//当たったマップチップの矩形
		HitMap(chipRect);//マップとの接地判定

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
		if (m_pos.x < static_cast<float>(stageEnd) - Graphic::screen_width + size_width / 2)
		{
			m_pos.x = static_cast<float>(stageEnd) - Graphic::screen_width + size_width / 2;
			//壁にぶつかった判定で、velを0にする
			m_velocity.x = 0.0f;
		}

		if (isColWall)
		{
			//壁にぶつかったのでエフェクトを消す
			if (auto rushEffect = m_rushEffect.lock())
			{
				rushEffect->Kill();
			}

			//壁にぶつかったエフェクトを出す
			Vector2 effectPos = m_pos;
			effectPos.y -= rush_effect_offset_y;//エフェクトの位置調整
			m_pEffectFactory->Create(effectPos, EffectType::hitWall);

			//ステートをアイドルに戻す
			m_state = State::Idle;
			m_isRushing = false;
			ctx.pCamera->OnImpact(shake_power);
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
		Charactor::Update(ctx);

		Rect chipRect;	//当たったマップチップの矩形
		HitMap(chipRect);//マップとの接地判定

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
			const Vector2 offset = { 0.0f,0.0f };
			m_rushEffect = m_pEffectFactory->CreateFollow(shared_from_this(), EffectType::rush, offset);
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

		Charactor::Update(ctx);

		Rect chipRect;	//当たったマップチップの矩形
		HitMap(chipRect);//マップとの接地判定

		//ランダムな攻撃方法をとる
		Attack(ctx.pEnemyBullets, ctx.pPlayer);
	}
}
