#include "Player.h"
#include "Geometry.h"
#include <DxLib.h>
#include "GameConstants.h"

Player::Player():
	Object({ 0.0f,0.0f }, { 0.0f,0.0f })
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
	m_pos.x++;
}

void Player::Draw()
{
	DrawCircle(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), 20, 0xffffff, false, 2);
}
