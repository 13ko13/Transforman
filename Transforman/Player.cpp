#include "Player.h"
#include "Geometry.h"
#include <DxLib.h>

Player::Player():
	Object({ 0.0f,0.0f }, { 0.0f,0.0f })
{
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update()
{
}

void Player::Draw()
{
	DrawCircle(m_pos.x, m_pos.y, 10, 0xffffff, false, 3);
}
