#include "Player.h"
#include "Geometry.h"
#include <DxLib.h>
#include "GameConstants.h"
#include "PlayerBullet.h"

namespace
{
	constexpr float ground = Graphic::screen_height - 100;	//地面の高さ(仮)
	constexpr float move_speed = 3.0f;							//移動速度
	constexpr float size_width = 32.0f;						//キャラクターの横幅
	constexpr float size_height = 64.0f;						//キャラクターの高さ

	constexpr int max_jump_frame = 15;
	constexpr float jump_power = -10.0f;

	constexpr int shot_cooltime = 10;							//ショットのクールタイム
	constexpr int prev_charge_time = 30;					//ショットからチャージショットになるまでの猶予フレーム
	constexpr int charge_time = 60;							//チャージしはじめて、撃てるまでのフレーム
}

Player::Player() :
	Object({ 0.0f,0.0f }, { 0.0f,0.0f }),
	m_isJumping(false),
	m_isGround(false),
	m_isRight(false),
	m_jumpFrame(0),
	m_shotCooltime(0),
	m_state(PlayerState::None),
	m_prevChargeFrame(0),
	m_chargeFrame(0)
{

}

Player::~Player()
{

}

void Player::Init()
{
	m_pos = { Graphic::screen_width / 2,Graphic::screen_height / 2 };
	m_sizeWidth = 32;
	m_sizeHeight = 64;
}

void Player::Update()
{
}

void Player::Update(Input& input, std::vector<std::shared_ptr<PlayerBullet>>& pBullets)
{
	m_frame++;
	//プレイヤーの中心座標を基準にする
	m_colRect.SetCenter(m_pos.x, m_pos.y, m_sizeWidth, m_sizeHeight);

	//重力を計算
	Gravity();
	//ジャンプ
	Jump(input);
	//移動
	Move(input);
	//ショット
	m_shotCooltime--;
	if (m_shotCooltime < 0)
	{
		m_shotCooltime = 0;
	}
	if (input.IsTriggerd("shot") &&
		m_shotCooltime == 0)
	{
		Shot(pBullets);
		m_shotCooltime = shot_cooltime;
	}
	
	

	//ボタンが一定フレーム以上
	//長押しされたらチャージショットの判定にする
	if (input.IsPressed("shot"))
	{
		m_chargeFrame++;

		if (m_chargeFrame > prev_charge_time)
		{
			//チャージショット
			ChargeShot(pBullets);
		}
	}

	//仮の地面を設定
	if (m_pos.y >= ground - 20)
	{
		m_pos.y = ground - 20;
		m_isGround = true;
		m_velocity.y = 0.0f;
	}

	//None,
	//Idle,
	//Walk,
	//Shot,
	//Jump,
	//ChageShot,
	//Climb,
	//Fire
	switch (m_state)
	{
	case PlayerState::Idle:

		break;
	case PlayerState::Walk:
		break;
	case PlayerState::Shot:
		break;
	case PlayerState::Jump:
		break;
	case PlayerState::ChageShot:
		break;
	case PlayerState::Climb:
		break;
	case PlayerState::Fire:
		break;
	}
}

void Player::Draw()
{
	

#if _DEBUG
	m_colRect.Draw(0xffffff, false);
	DrawFormatString(0, 0, 0xffffff, L"frame:%d", m_frame);
	DrawFormatString(0, 15, 0xffffff, L"playerPosY:%f", m_pos.y);
	DrawFormatString(0, 30, 0xffffff, L"isRight:%d", m_isRight);
	DrawFormatString(0, 60, 0xffffff, L"shotCoolTime:%d", m_shotCooltime);
	DrawFormatString(0, 150, 0xffffff, L"chargeFrame:%d", m_chargeFrame);
#endif
}

void Player::Jump(Input& input)
{
	if (input.IsPressed("jump") && m_isGround)
	{
		//地面にいる状態でジャンプボタンを押されるとジャンプ
		// 可能状態になる
		m_isJumping = true;
	}
	//ジャンプを入力した、かつ、ジャンプ可能状態だったら
	if (input.IsPressed("jump"))
	{
		if (m_isJumping)
		{
			m_jumpFrame++;
			m_isGround = false;
			if (m_jumpFrame < max_jump_frame)
			{
				m_velocity.y = jump_power;
			}
		}
	}
	else
	{
		m_jumpFrame = 0;
		m_isJumping = false;
	}
}

void Player::Move(Input& input)
{
	m_pos += m_velocity;

	Vector2 dir = { 0.0f,0.0f };//プレイヤーの速度ベクトル
	if (input.IsPressed("right"))
	{
		dir.x = 1.0f;
		m_isRight = true;
	}
	if (input.IsPressed("left"))
	{
		dir.x = -1.0f;
		m_isRight = false;
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
			bullet->SetIsAlive(true);
			bullet->SetIsRight(m_isRight);
			break;	//1発撃ったらループを抜ける
		}
	}
}

void Player::ChargeShot(std::vector<std::shared_ptr<PlayerBullet>>& pBullets)
{
	DrawFormatString(0, 165, 0xffffff, L"チャージ中！");
	m_chargeFrame++;
	if (m_chargeFrame > charge_time)
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
				bullet->BulletType::Charge;
				bullet->SetIsAlive(true);
				bullet->SetIsRight(m_isRight);
				break;	//1発撃ったらループを抜ける
			}
		}
	}

}
