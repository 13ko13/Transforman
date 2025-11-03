#include "Player.h"
#include "Geometry.h"
#include <DxLib.h>
#include "GameConstants.h"

namespace
{
	constexpr float ground = Graphic::screen_height - 100;
	constexpr float move_speed = 3.0f;
	constexpr float jump_power = -15.0;
}

Player::Player():
	Object({ 0.0f,0.0f }, { 0.0f,0.0f }),
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
	DrawCircle(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), 20, 0xffffff, false, 2);

	DrawLine(0, ground, Graphic::screen_width, ground, 0xffffff, 1);
	DrawFormatString(0, 0, 0xffffff, L"%f,%f", m_velocity.x, m_velocity.y);
}

void Player::Jump(Input& input)
{
	if (input.IsTriggerd("jump") && !m_isJump)
	{
		m_velocity.y = jump_power;
		m_isJump = true;
	}
}
