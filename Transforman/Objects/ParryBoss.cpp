#include "ParryBoss.h"
#include <Dxlib.h>
#include "../Graphics/Camera.h"
#include <cassert>

namespace
{
	constexpr int size_width = 80;
	constexpr int size_height = 80;

	//初期位置
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
		5.0, 0.0,
		m_handle,
		true, false);

	//デバッグ用当たり判定表示
#if _DEBUG
	m_colRect.Draw(0xff0000, false, pCamera);
#endif
}

void ParryBoss::OnArrive()
{

}

void ParryBoss::Attack()
{
}
