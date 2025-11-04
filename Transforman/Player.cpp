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

	constexpr float low_jump_power  = -8.0f;						//低ジャンプの時のジャンプ力
	constexpr float low_jump_input  = 3.0f;							//低ジャンプ時の入力猶予フレーム
	constexpr float mid_jump_power  = -11.0f;						//中ジャンプの時のジャンプ力
	constexpr float mid_jump_input  = 3.0f;							//中ジャンプ時の入力猶予フレーム
	constexpr float high_jump_power = -8.0f;						//高ジャンプの時のジャンプ力
	constexpr float high_jump_input = 3.0f;							//高ジャンプ時の入力猶予フレーム
}

Player::Player():
	Object({ 0.0f,0.0f }, { 0.0f,0.0f }),
	m_jumpInputFrame(0.0f),
	m_isJump(false)
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
	}
	if (input.IsPressed("left"))
	{
		dir.x = -1.0f;
	}

	

	//ディレクションを正規化してプレイヤーのスピードをかけて
	//ポジションに足してあげる移動処理
	m_pos += dir.Normalized() * move_speed;

	//仮の地面を設定
	if (m_pos.y >= ground - 20)
	{
		m_pos.y = ground - 20;
		m_isJump = false;
	}
}

void Player::Draw()
{
	DrawFormatString(0, 0, 0xffffff, L"%f,%f", m_velocity.x, m_velocity.y);
	m_colRect.Draw(0xffffff, false);
}

void Player::Jump(Input& input)
{
	if (input.IsTriggerd("jump") && !m_isJump)
	{
		//ジャンプの高さを決めるフレームを計算する
		m_frame++;
		//低ジャンプ
		if (m_frame >= low_jump_input)
		{
			m_velocity.y = low_jump_power;
			m_isJump = true;
		}
		//中ジャンプ
		else if (m_frame >= mid_jump_input)
		{
			m_velocity.y = mid_jump_power;
			m_isJump = true;
		}
		//高ジャンプ
		else if (m_frame >= high_jump_input)
		{
			m_velocity.y = high_jump_power;
			m_isJump = true;
		}
	}
}
