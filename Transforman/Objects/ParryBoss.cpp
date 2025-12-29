#include "ParryBoss.h"
#include <Dxlib.h>
#include "../Graphics/Camera.h"
#include <cassert>

namespace
{
	constexpr int size_width = 30;
	constexpr int size_height = 30;

	//èâä˙à íu
	const Vector2 first_pos = { 500.0f, 500.0f };
}

ParryBoss::ParryBoss(std::shared_ptr<Map> pMap) :
	EnemyBase(size_width, size_height, pMap)
{
	m_handle = LoadGraph("img/game/Enemy/parry_boss.png");
	assert(m_handle >= 0);

	m_pos = first_pos;
}

ParryBoss::~ParryBoss()
{

}

void ParryBoss::Init()
{

}

void ParryBoss::Update(GameContext& ctx)
{

}

void ParryBoss::Draw(std::shared_ptr<Camera> pCamera)
{
	DrawRectRotaGraph(
		m_pos.x + pCamera->GetDrawOffset().x,
		m_pos.y + pCamera->GetDrawOffset().y,
		0, 0,
		size_width, size_height,
		1.0f, 0.0f,
		m_handle,
		true, false);
}

void ParryBoss::OnArrive()
{
}

void ParryBoss::Attack()
{
}
