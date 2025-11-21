#include "Player.h"
#include "Geometry.h"
#include <DxLib.h>
#include "GameConstants.h"
#include "PlayerBullet.h"
#include "Camera.h"

namespace
{
	constexpr float ground = Graphic::screen_height - 100;	//地面の高さ(仮)
	constexpr float move_speed = 3.0f;							//移動速度
	constexpr float size_width = 40.0f;						//キャラクターの横幅
	constexpr float size_height = 50.0f;					//キャラクターの高さ
	constexpr float graph_width = 40.0f;					//画像の横切り取りサイズ
	constexpr float graph_height = 40.0f;					//画像の縦切り取りサイズ

	constexpr double   draw_scale = 1.5;					//描画スケール			

	constexpr int max_jump_power = 10.0f;					//最大ジャンプ力
	constexpr int min_jump_power = 8.0f;					//最低ジャンプ力
	constexpr float jump_scale = 1.4f;							//ジャンプ力の倍率

	constexpr int shot_cooltime = 30;						//ショットのクールタイム
	constexpr int prev_charge_time = 30;					//ショットからチャージショットになるまでの猶予フレーム

	//アニメーション用のグラフのインデックス
	constexpr int graph_index_idle = 0;
	constexpr int graph_index_walk = 1;
	constexpr int graph_index_damage = 3;
	constexpr int graph_index_deth = 7;
	constexpr int graph_index_jump = 8;

	constexpr int anim_wait_frame = 10;						//次のアニメーションまでの待機時間
	constexpr int idle_anim_frame = 4;						//アイドルアニメーションの枚数
	constexpr int walk_anim_frame = 7;						//歩き状態のアニメーションの枚数
	constexpr int damage_anim_frame = 8;					//食らい状態のアニメーション枚数
	constexpr int deth_anim_frame = 20;						//死んだときのアニメーション枚数
	constexpr int jump_anim_frame = 3;						//ジャンプの時のアニメーション枚数

}

Player::Player() :
	Object({ 0.0f,0.0f }, { 0.0f,0.0f }),
	m_isJumping(false),
	m_isGround(false),
	m_isRight(false),
	m_isCharging(false),
	m_isDead(false),
	m_jumpPower(0),
	m_shotCooltime(0),
	m_state(PlayerState::Idle),
	m_prevChargeFrame(0),
	m_animFrame(0),
	m_animSrcX(0),
	m_animSrcY(0),
	m_animIdx(0)
{
	m_handle = LoadGraph("img/game/Player/player.png");
	m_colRect.SetLT(
		m_pos.x, m_pos.y,
		size_width ,size_height);
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
	m_frame++;
	m_pos += m_velocity;
	m_animFrame++;

	//重力を計算
	Gravity();

	//押されている間ジャンプ力が可変する
	//ジャンプボタンが離されるor最大ジャンプ力を超えたら強制的に
	//ジャンプさせる
	if (ctx.input.IsPressed("jump") &&
		m_isGround)
	{
		m_jumpPower--;
	}
	if ((ctx.input.IsReleased("jump") ||
		abs(m_jumpPower) > max_jump_power ) &&
		m_isGround)
	{
		Jump(ctx.input);
	}

	//移動
	Move(ctx.input);

	//ショットの準備
	PrevShot(ctx.input, ctx.p_playerBullets);

	//壁のぼり
	if (ctx.input.IsPressed("up"))
	{
		Climb();
	}


	//仮の地面を設定
	if (m_pos.y >= ground)
	{
		m_pos.y = ground;
		m_isGround = true;
		m_velocity.y = 0.0f;
	}
	else
	{
		m_isGround = false;
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
	//1フレーム進むごとにアニメーションが1枚進む
	int AnimNo = m_animFrame / anim_wait_frame;
	m_animSrcX = graph_width * AnimNo;
	m_animSrcY = graph_height * m_animIdx;
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
	case PlayerState::Climb:

		break;
	case PlayerState::Fire:

		break;
	}

	//現在のアニメーションのフレーム数が
	//現在のステートの描画枚数を超えたら現在のアニメーションの
	//現在のアニメーションのフレーム数を0にする
	if (m_animFrame >= animMax * anim_wait_frame)
	{
		m_animFrame = 0.0f;
	}

	//プレイヤーの左上座標を基準にする
	m_colRect.SetLT(m_pos.x - size_width / 2, m_pos.y - size_height / 2 + 5, size_width, size_height);
}

void Player::Draw(Camera camera)
{
#if _DEBUG
	m_colRect.Draw(0xffffff, false,camera);
	DrawFormatString(0, 0, 0xffffff, "frame:%d", m_frame);
	DrawFormatString(0, 15, 0xffffff, "playerPosY:%f", m_pos.y);
	DrawFormatString(0, 30, 0xffffff, "isRight:%d", m_isRight);
	DrawFormatString(0, 60, 0xffffff, "shotCoolTime:%d", m_shotCooltime);
	DrawFormatString(0, 150, 0xffffff, "prevChargeFrame:%d", m_prevChargeFrame);
	DrawFormatString(0, 165, 0xffffff, "ground : %d", m_isGround);
	DrawFormatString(0, 180, 0xffffff, "jumpPower : %d", m_jumpPower);
	DrawFormatString(0, 195, 0xffffff, "velocity(%f , %f)", m_velocity.x, m_velocity.y);
#endif

	DrawRectRotaGraph(
		static_cast<int>(m_pos.x + camera.GetDrawOffset().x), static_cast<int>(m_pos.y + camera.GetDrawOffset().y), //表示位置
		m_animSrcX, m_animSrcY,												//切り取り開始位置
		graph_width, graph_height,								//切り取りサイズ
		draw_scale, 0.0,											//拡大率、回転角度
		m_handle,											//画像ハンドル
		true,												//透明度
		!m_isRight											//反転
	);
}

void Player::Jump(Input& input)
{
	m_state = PlayerState::Jump;
	//プレイヤーが一瞬しか押さないと全くジャンプしないので
	// 一定以下のフレームしか押されなかったら
	//最低ジャンプ力をきめて
	//そのジャンプ力で飛ぶ
	if (abs(m_jumpPower) < min_jump_power)
	{
		m_jumpPower = -min_jump_power;
	}
	m_velocity.y += static_cast<float>(m_jumpPower * jump_scale);
	m_pos.y += m_velocity.y;
	m_jumpPower = 0;
}

void Player::Move(Input& input)
{
	Vector2 dir = { 0.0f,0.0f };//プレイヤーの速度ベクトル
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

	//ディレクションを正規化してプレイヤーのスピードをかけて
	//ポジションに足してあげる移動処理
	m_pos += dir.Normalized() * move_speed;
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
			bullet->SetType(BulletType::Charge);
			bullet->SetIsAlive(true);
			bullet->SetIsRight(m_isRight);
			break;	//1発撃ったらループを抜ける
		}
	/*	else
		{
			m_state = PlayerState::Idle;
		}*/
	}
}

void Player::PrevShot(Input& input, std::vector<std::shared_ptr<PlayerBullet>>& pBullets)
{
	m_shotCooltime--;
	if (m_shotCooltime < 0)
	{
		//クールタイムを更新して0以下になったら
		//ショット可能状態にする
		m_shotCooltime = 0;
	}
	//ボタンが一定フレーム以上
	//長押しされたらチャージショットの判定にする
	//チャージショットの猶予時間を超えたらチャージショット
	//それ以外は通常ショット
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
		if (m_prevChargeFrame > prev_charge_time)
		{
			//チャージショット
			ChargeShot(pBullets);
			m_shotCooltime = shot_cooltime;
			m_prevChargeFrame = 0;
			m_isCharging = false;
		}
		else
		{
			//通常ショット
			Shot(pBullets);
			m_shotCooltime = shot_cooltime;
			m_prevChargeFrame = 0;
		}
	}
	//else
	//{
	//	m_state = PlayerState::Idle;
	//}
}

void Player::Climb()
{

}
