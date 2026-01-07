#include "Player.h"
#include "../Utility/Geometry.h"
#include <DxLib.h>
#include "../General/GameConstants.h"
#include "PlayerBullet.h"
#include "../Graphics/Camera.h"
#include <cassert>

namespace
{
	constexpr float ground = Graphic::screen_height - 220;	//地面の高さ(仮)
	constexpr int move_speed = 5;							//移動速度
	constexpr int debug_speed = 10;							//デバッグ用でプレイヤーのスピードを変えたときの値
	constexpr float size_width = 40.0f;						//キャラクターの横幅
	constexpr float size_height = 50.0f;					//キャラクターの高さ
	constexpr float graph_width = 40.0f;					//画像の横切り取りサイズ
	constexpr float graph_height = 40.0f;					//画像の縦切り取りサイズ
	constexpr int rect_offset_y = 12;						//キャラクターの場所と矩形の場所を合わせる(微妙に頭の上の当たり判定が大きくなってしまうため)
	constexpr double draw_scale = 2.0f;						//描画スケール	

	constexpr int knockback_duration = 15.0f;				//ノックバックする時間
	constexpr float knockback_speed = 15.0f;				//ノックバックするときのスピード
	constexpr float knockback_jump = -7.0f;					//縦のノックバック力

	constexpr int max_jump_frame = 15;						//最大ジャンプ入力時間
	constexpr float jump_power = 12.0f;						//ジャンプ力

	constexpr int shot_cooltime = 15;						//ショットのクールタイム
	constexpr int prev_charge_time = 30;					//ショットからチャージショットになるまでの猶予フレーム
	constexpr int max_blink_time = 60;						//点滅するフレーム数
	constexpr int flame_motion_frame = 30;					//火炎放射中の時間

	constexpr int parry_i_frame = 60;						//パリィ後の無敵時間
	constexpr int parry_cooltime = 0;						//パリィのクールタイム

	//アニメーション用のグラフのインデックス
	constexpr int graph_index_idle = 0;
	constexpr int graph_index_walk = 1;
	constexpr int graph_index_shot = 2;
	constexpr int graph_index_damage = 3;
	constexpr int graph_index_deth = 7;
	constexpr int graph_index_jump = 8;

	//アニメーション関係
	constexpr int anim_wait_frame = 7;						//次のアニメーションまでの待機時間
	constexpr int idle_anim_frame = 4;						//アイドルアニメーションの枚数
	constexpr int flame_anim_frame = 1;						//火炎放射中のアニメーションの枚数
	constexpr int walk_anim_frame = 7;						//歩き状態のアニメーションの枚数
	constexpr int damage_anim_frame = 8;					//食らい状態のアニメーション枚数
	constexpr int deth_anim_frame = 20;						//死んだときのアニメーション枚数
	constexpr int jump_anim_frame = 3;						//ジャンプの時のアニメーション枚数
}

Player::Player(std::shared_ptr<Map> pMap) :
	Charactor(size_width, size_height, pMap),
	m_isJumping(false),
	m_isPrevJump(false),
	m_isCharging(false),
	m_isArrive(false),
	m_isInvincible(false),
	m_isCanAction(true),
	m_jumpFrame(0),
	m_shotCooltime(0),
	m_flameThrowerCT(0),
	m_flameThrowCount(0),
	m_knockackTimer(0),
	m_blinkingTimer(0),
	m_state(PlayerState::Idle),
	m_weaponType(WeaponType::Normal),
	m_prevChargeFrame(0),
	m_animSrcX(0),
	m_animSrcY(0),
	m_animIdx(0),
	m_damageAnimFrame(0),
	m_knockbackDir(0),
	m_parryCooltime(0),
	m_iFrameTimer(0)
{
	m_handle = LoadGraph("img/game/Player/transforman_player.png");
	assert(m_handle >= 0);
}

Player::~Player()
{
	DeleteGraph(m_handle);
}

void Player::Init()
{
	m_pos = { Graphic::screen_width / 2,Graphic::screen_height / 2 };
}

void Player::Update(GameContext& ctx)
{
#if _DEBUG
	//デバッグ処理
	Debug(ctx.input);
#endif

	//フレームを更新
	m_frame++;
	//アニメーションフレームの更新
	m_animFrame++;

	//クールタイムを更新して0以下になったら
	//ショット可能状態にする
	m_shotCooltime--;
	//クールタイムを更新して0以下になったら
	//パリィ可能状態にする
	m_parryCooltime--;

	//ダメージ状態中または火炎放射中は行動できないようにする
	if (m_isCanAction)
	{
		//移動
		Move(ctx.input);
		//ジャンプを長押ししていて、地面についているなら
		//ジャンプ中
		if (ctx.input.IsPressed("jump"))
		{
			if (m_isGround)
			{
				m_isJumping = true;
			}
			//ジャンプ
			Jump();
		}
		else
		{
			//ジャンプが入力されていないなら
			//ジャンプ中を解除
			m_jumpFrame = 0;
			m_isJumping = false;
		}

		//クールタイムが0以下の場合ショットの準備を進める
		if (m_shotCooltime <= 0)
		{
			PrevShot(ctx.input, ctx.pPlayerBullets);
		}

		//プレイヤーがパリィボタンを押したらパリィを発動
		if (ctx.input.IsTriggered("parry") && 
			m_parryCooltime < 0 &&
			m_isGround &&
			m_state != PlayerState::Damage)
		{
			//状態をパリィに変更
			m_state = PlayerState::Parry;
			OnParry();
			printfDx("パリィをした");
		}
	}

	Charactor::Update(ctx);
	Rect chipRect;	//当たったマップチップの矩形
	HitMap(chipRect);//マップとの接地判定
	//火炎放射もクールタイムを更新して0以下になったら
	//放射可能状態にする
	m_flameThrowerCT--;

	//無敵中
	if (m_isInvincible)
	{
		m_blinkingTimer--;
		if (m_blinkingTimer < 0)
		{
			m_isInvincible = false;
		}
	}
	
	//None,
	//Idle,
	//Walk,
	//Shot,
	//Jump,
	//ChageShot,
	//Climb,
	//Fire
	//アニメーションのフレーム数から表示したいコマ番号を計算で求める
	//anim_wait_frame進むごとにアニメーションが1枚進む
	int AnimNo = m_animFrame / anim_wait_frame;
	m_animSrcX = graph_width * AnimNo;//現在表示したいStateのアニメーションの横切り取り位置
	m_animSrcY = graph_height * m_animIdx;//現在表示したいStateのアニメーションの縦切り取り位置
	int animMax = 0;
	switch (m_state)
	{
	case PlayerState::Idle:
		m_animSrcY = graph_height * graph_index_idle;
		animMax = idle_anim_frame;
		break;
	case PlayerState::Walk:
		m_animSrcY = graph_height * graph_index_walk;
		animMax = walk_anim_frame;
		break;
	case PlayerState::Shot:
	case PlayerState::ChargeShot:

		break;
	case PlayerState::Jump:
		m_animSrcY = graph_height * graph_index_jump;
		animMax = jump_anim_frame;
		break;
	case PlayerState::Parry:
		//パリィ更新処理
		m_isInvincible = true;
		m_iFrameTimer--;
		if (m_iFrameTimer < 0)
		{
			//ステートを戻す
			m_state = PlayerState::Idle;
		}
		break;
	case PlayerState::Fire:
		//行動不能にする
		m_isCanAction = false;
		m_animSrcY = graph_height * graph_index_shot;
		animMax = flame_anim_frame;
		m_velocity.x = 0.0f;
		m_flameThrowCount--;
		if (m_flameThrowCount <= 0)
		{
			m_state = PlayerState::Idle;
			m_isCanAction = true;
		}
		break;
	case PlayerState::Damage:
		//無敵を有効にする
		m_isInvincible = true;
		//ノックバックさせる
		UpdateKnockback();
		//行動不能にする
		m_isCanAction = false;
		//画像の縦切り取り位置
		m_animSrcY = graph_height * graph_index_damage;
		//アニメーションの一番最後のフレーム数を保存
		animMax = damage_anim_frame;
		//ダメージのみ切り取り位置を補正
		m_animSrcX = graph_width * ((int)m_damageAnimFrame / anim_wait_frame);
		//ダメージアニメーションが終わったら
		//StateをIdleに切り替える
		m_damageAnimFrame++;
		if (m_damageAnimFrame >= animMax * anim_wait_frame)
		{
			//idleに戻った後の無敵時間を設定
			m_blinkingTimer = max_blink_time;
			m_damageAnimFrame = 0;
			m_isCanAction = true;
			m_state = PlayerState::Idle;
		}
		break;
	}
	//現在のアニメーションのフレーム数が
	//現在のステートの描画枚数を超えたら
	//現在のアニメーションのフレーム数を0にする
	if (m_animFrame >= animMax * anim_wait_frame)
	{
		m_animFrame = 0.0f;
	}


	//ボス部屋に到着している場合
	//そこから出られないように
	//プレイヤーを押し戻しする
	if (m_isArrive &&
		m_pos.x < Graphic::screen_width + size_width * 0.5f)
	{
		m_pos.x = Graphic::screen_width + size_width * 0.5f;
	}
}

void Player::Draw(std::shared_ptr<Camera> pCamera)
{
#if _DEBUG
	Charactor::Draw(pCamera);
	DrawFormatString(0, 0, 0xffffff, "Frame:%d", m_frame);
	DrawFormatString(0, 15, 0xffffff, "PlayerPosX:%f, Y: %f", m_pos.x, m_pos.y);
	DrawFormatString(0, 30, 0xffffff, "IsRight:%d", m_isRight);
	DrawFormatString(0, 45, 0xffffff, "JumpFrame : %d", m_jumpFrame);
	DrawFormatString(0, 60, 0xffffff, "ShotCoolTime:%d", m_shotCooltime);
	DrawFormatString(0, 150, 0xffffff, "PrevChargeFrame:%d", m_prevChargeFrame);
	DrawFormatString(0, 165, 0xffffff, "Ground : %d", m_isGround);
	DrawFormatString(0, 195, 0xffffff, "Velocity(%f , %f)", m_velocity.x, m_velocity.y);
	DrawFormatString(0, 210, 0xffffff, "PlayerState : %d", m_state);
	DrawFormatString(0, 225, 0xffffff, "DamageAnimFrame : %f", m_damageAnimFrame);
	DrawFormatString(0, 240, 0xffffff, "BlinkingTimer : %d", m_blinkingTimer);
	DrawFormatString(0, 255, 0xffffff, "WeaponType : %d", m_weaponType);
	DrawFormatString(0, 385, 0xffffff, "IsCanAction : %d", m_isCanAction);
	DrawFormatString(0, 400, 0xffffff, "ParryTimer : %d", m_iFrameTimer);
	DrawFormatString(0, 415, 0xffffff, "ParryCooltime : %d", m_parryCooltime);
#endif

	//操作方法
	DrawFormatString(Graphic::screen_width - 160, 64, 0xffffff, "Jump : B");
	DrawFormatString(Graphic::screen_width - 160, 64 + 15, 0xffffff, "Shot : A");
	DrawFormatString(Graphic::screen_width - 160, 64 + 30, 0xffffff, "Move : Lスティック");
	DrawFormatString(Graphic::screen_width - 160, 64 + 45, 0xffffff, "Parry : X");

	//ダメージ受けたときは一定時間表示する→しないを繰り返して
	//無敵時間を表す
	if (m_isInvincible)
	{
		//点滅
		if (m_blinkingTimer % 5 == 0)
		{
			DrawRectRotaGraph(
				static_cast<int>(m_pos.x + pCamera->GetDrawOffset().x),
				static_cast<int>(m_pos.y + pCamera->GetDrawOffset().y) - rect_offset_y, //表示位置
				m_animSrcX, m_animSrcY,												//切り取り開始位置
				graph_width, graph_height,								//切り取りサイズ
				draw_scale, 0.0,											//拡大率、回転角度
				m_handle,											//画像ハンドル
				true,												//透明度
				!m_isRight											//反転
			);
		}
		else
		{

		}
	}
	else
	{
		//無敵中じゃないときは常に表示
		DrawRectRotaGraph(
			static_cast<int>(m_pos.x + pCamera->GetDrawOffset().x),
			static_cast<int>(m_pos.y + pCamera->GetDrawOffset().y) - rect_offset_y, //表示位置
			m_animSrcX, m_animSrcY,												//切り取り開始位置
			graph_width, graph_height,								//切り取りサイズ
			draw_scale, 0.0,											//拡大率、回転角度
			m_handle,											//画像ハンドル
			true,												//透明度
			!m_isRight											//反転
		);
	}

}

void Player::OnArriveEnemy()
{
	m_isArrive = true;
	m_isCanAction = false;
	m_velocity.x = 0.0f;
	m_state = PlayerState::Idle;
}

void Player::Jump()
{
	if (m_state == PlayerState::Damage ||
		m_state == PlayerState::Parry) return;
	//ジャンプを長押ししていないなら飛ばす
	if (!m_isJumping) return;

	m_jumpFrame++;
	m_isGround = false;
	if (m_jumpFrame < max_jump_frame)
	{
		m_velocity.y = -jump_power;
	}
}

void Player::Move(Input& input)
{
	//ダメージを受けているときと炎を放っているときと
	//パリィを行っているときは
	//処理を行わない
	if (m_state == PlayerState::Damage ||
		m_state == PlayerState::Fire ||
		m_state == PlayerState::Parry) return;

	Vector2 dir = { 0.0f,0.0f };//プレイヤーの速度ベクトル
	m_velocity.x = 0.0f;
	if (input.IsPressed("right"))
	{
		m_state = PlayerState::Walk;
		dir.x = 1.0f;
		m_isRight = true;
	}
	else if (input.IsPressed("left"))
	{
		m_state = PlayerState::Walk;
		dir.x = -1.0f;
		m_isRight = false;
	}
	else
	{
		m_state = PlayerState::Idle;
	}
	int speed = move_speed;
#ifdef _DEBUG
	//デバッグ用のプレイヤーのスピードアップ
	if (input.IsPressed("playerSpeedUp"))
	{
		speed = debug_speed;
	}
#endif // _DEBUG
	//ディレクションを正規化してプレイヤーのスピードをかけて
	//ポジションに足してあげる移動処理
	m_velocity += dir.Normalized() * speed;
}

void Player::Shot(std::vector<std::shared_ptr<PlayerBullet>>& pBullets)
{
	for (auto& bullet : pBullets)
	{
		if (!bullet->GetIsAlive())
		{
			//弾が存在していない場合、弾を発射する
			if (m_isRight)
			{
				//右向き
				bullet->SetPos({ m_pos.x + size_width / 2, m_pos.y });
			}
			else
			{
				//左向き
				bullet->SetPos({ m_pos.x - size_width / 2 , m_pos.y });
			}
			bullet->SetType(BulletType::Normal);
			bullet->SetIsAlive(true);
			bullet->SetIsRight(m_isRight);
			break;	//1発撃ったらループを抜ける
		}
	}

}

void Player::ChargeShot(std::vector<std::shared_ptr<PlayerBullet>>& pBullets)
{
	for (auto& bullet : pBullets)
	{
		if (!bullet->GetIsAlive())
		{
			//弾が存在していない場合、弾を発射する
			if (m_isRight)
			{
				//右向き
				bullet->SetPos({ m_pos.x + size_width / 2, m_pos.y });
			}
			else
			{
				//左向き
				bullet->SetPos({ m_pos.x - size_width / 2 , m_pos.y });
			}
			bullet->SetType(BulletType::Charge);
			bullet->SetIsAlive(true);
			bullet->SetIsRight(m_isRight);
			break;	//1発撃ったらループを抜ける
		}
	}
}

void Player::FireShot(std::vector<std::shared_ptr<PlayerBullet>>& pBullets)
{
	//地面についているときのみ発射OKとする
	if (!m_isGround) return;

	for (auto& bullet : pBullets)
	{
		if (bullet->GetIsAlive()) return;

		bullet->OnFlame();
		//弾が存在していない場合、弾を発射する
		if (m_isRight)
		{
			//右向き
			bullet->SetPos({ m_pos.x + size_width / 2, m_pos.y });
			////状態遷移
			//m_state = PlayerState::ChargeShot;
		}
		else
		{
			//左向き
			bullet->SetPos({ m_pos.x - size_width / 2 , m_pos.y });
			////状態遷移
			//m_state = PlayerState::ChargeShot;
		}
		bullet->SetType(BulletType::Fire);
		bullet->SetIsAlive(true);
		bullet->SetIsRight(m_isRight);
		//火炎放射中の時間を計測する変数に代入
		m_flameThrowCount = flame_motion_frame;
		break;	//1発撃ったらループを抜ける

	}
}

void Player::PrevShot(Input& input, std::vector<std::shared_ptr<PlayerBullet>>& pBullets)
{
	if (m_state != PlayerState::Damage)
	{
		//ボタンが一定フレーム以上
		//長押しされたらチャージショットの判定にする
		//チャージショットの猶予時間を超えたらチャージショット
		//それ以外は通常ショット
		//もしくは火炎放射
		if (input.IsPressed("shot"))
		{
			m_prevChargeFrame++;
			m_isCharging = true;
#if _DEBUG
			DrawFormatString(0, 230, 0xffffff, "チャージ中！");
#endif
		}
		if (input.IsReleased("shot"))
		{
			if (m_prevChargeFrame > prev_charge_time &&
				m_shotCooltime < 0)
			{
				//チャージショット
				ChargeShot(pBullets);
				m_isCharging = false;
			}
			else if (m_prevChargeFrame < prev_charge_time &&
				m_weaponType == WeaponType::Normal &&
				m_shotCooltime < 0)
			{
				//通常ショット
				Shot(pBullets);
			}
			else if (m_prevChargeFrame < prev_charge_time &&
				m_weaponType == WeaponType::Fire &&
				m_shotCooltime < 0)
			{
				//火炎放射
				FireShot(pBullets);
				m_state = PlayerState::Fire;
			}
			m_shotCooltime = shot_cooltime;
			m_prevChargeFrame = 0;
		}
	}
}

void Player::OnParry()
{
	m_parryCooltime = parry_cooltime;
	m_iFrameTimer = parry_i_frame;
	m_velocity.x = 0.0f;
}

void Player::ChangeState(PlayerState state)
{
	m_state = state;
}

void Player::UpdateKnockback()
{
	//残りノックバック時間を減らしていく
	m_knockackTimer--;
	//プレイヤーが右を向いている場合は
	//Xはマイナス側に進んでいくので
	//ノックバックした後に徐々に0に近づけて
	//自然なノックバックにする
	if (m_isRight)
	{
		m_velocity.x++;
		if (m_velocity.x >= 0)
		{
			m_velocity.x = 0.0f;
		}
	}
	else
	{
		m_velocity.x--;
		if (m_velocity.x <= 0)
		{
			m_velocity.x = 0.0f;
		}
	}
}

void Player::Debug(Input& input)
{
	//デバッグ用の武器タイプ切り替え
	if (input.IsTriggered("changeState(player)"))
	{
		if (m_weaponType == WeaponType::Normal)
		{
			m_weaponType = WeaponType::Fire;
			return;
		}
		if (m_weaponType == WeaponType::Fire)
		{
			m_weaponType = WeaponType::Normal;
			return;
		}
	}
	if (input.IsTriggered("parry"))
	{
		m_parryCooltime = -1;
	}
}

void Player::OnKnockback(int dir)
{
	//チャージ状態や、火炎放射中だと
	//引き継がれたままダメージを受けるので
	//一度アイドルにリセットする
	m_state = PlayerState::Idle;
	m_state = PlayerState::Damage;//ステートを切り替える
	m_knockackTimer = knockback_duration;//ノックバックする時間を決める
	m_knockbackDir = dir;//ノックバックする方向を代入

	//ノックバックするための方向と速度を代入する
	m_velocity.x = m_knockbackDir * knockback_speed;
	m_velocity.y = knockback_jump;
}

void Player::OnStart()
{
	//行動可能にする
	m_isCanAction = true;
}
