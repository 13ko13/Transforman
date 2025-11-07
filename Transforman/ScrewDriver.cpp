#include "ScrewDriver.h"

namespace
{
	constexpr int size_width = 32;//幅
	constexpr int size_height = 32;//高さ

	const Vector2 first_pos = { 500.0f,500.0f };
}

ScrewDriver::ScrewDriver()
{

}

ScrewDriver::~ScrewDriver()
{
}

void ScrewDriver::Init()
{
	m_pos = first_pos;
	m_sizeWidth = size_width;
	m_sizeHeight = size_height;
}

void ScrewDriver::Update()
{
	//スクリュードライバーの中心座標を基準にする
	m_colRect.SetCenter(m_pos.x, m_pos.y, m_sizeWidth, m_sizeHeight);
}

void ScrewDriver::Draw()
{
#if _DEBUG
	m_colRect.Draw(0xaaffff,false);
#endif
}

void ScrewDriver::Attack()
{
	//弾を撃つ
	
}