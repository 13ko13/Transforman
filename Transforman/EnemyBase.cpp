#include "EnemyBase.h"
#include "Camera.h"

EnemyBase::EnemyBase() :
	Object({ 0.0f,0.0f }, { 0.0f,0.0f })
{
	m_pColRect = std::make_shared<Rect>();
	m_pColRect->SetLT(
		m_pos.x, m_pos.y,
		m_pos.x + m_sizeWidth,
		m_pos.y + m_sizeHeight);
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init()
{

}

void EnemyBase::Update()
{
	m_pColRect->SetLT(
		m_pos.x, m_pos.y,
		m_pos.x + m_sizeWidth,
		m_pos.y + m_sizeHeight);
}

void EnemyBase::Draw(Camera camera)
{

}

void EnemyBase::Attack()
{

}