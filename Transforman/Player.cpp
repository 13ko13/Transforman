#include "Player.h"
#include "Geometry.h"
#include <DxLib.h>
#include "GameConstants.h"

namespace
{
	constexpr float ground          = Graphic::screen_height - 100;	//地面の高さ(仮)
	constexpr float move_speed      = 3.0f;							//移動速度
	constexpr float size_width      = 32.0f;						//キャラクターの横幅
	constexpr float size_height     = 64.0f;						//キャラクターの高さ

	constexpr int max_jump_frame	= 15;
	constexpr float jump_power		= -9.0f;
}

Player::Player():
	Object({ 0.0f,0.0f }, { 0.0f,0.0f }),
	m_isJumping(false),
	m_isGround(false),
	m_isRight(false),
	m_jumpFrame(0.0f)
{
	
}

Player::~Player()
{

}

void Player::Init()
{
	m_pos = { Graphic::screen_width / 2,Graphic::screen_height / 2 };
}

void Player::Update()
{
}

void Player::Update(Input& input)
{
	//プレイヤーの中心座標を基準にする
	m_colRect.SetCenter(m_pos.x, m_pos.y, size_width, size_height);

	//重力を計算
	Gravity();
	//ジャンプ
	Jump(input);
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

	//仮の地面を設定
	if (m_pos.y >= ground - 20)
	{
		m_pos.y = ground - 20;
		m_isGround = true;
	}
}

void Player::Draw()
{
	DrawFormatString(0, 20, 0xffffff, L"%f,%f", m_velocity.x, m_velocity.y);
	DrawFormatString(0, 0, 0xffffff, L"%f",m_frame);

#if _DEBUG
	m_colRect.Draw(0xffffff, false);
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
