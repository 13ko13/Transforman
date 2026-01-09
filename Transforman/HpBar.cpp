#include "HpBar.h"

HpBar::HpBar(int maxHitPoint) :
	UserInterface({0,0},m_handle),
	m_hitPoint(0),
	m_maxHitPoint(maxHitPoint)
{
	//HPÇê›íË
	m_hitPoint = m_maxHitPoint;
}

HpBar::~HpBar()
{
}

void HpBar::Update()
{
}

void HpBar::Draw()
{
}
