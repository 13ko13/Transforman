#include "Object.h"
#include <DxLib.h>

namespace
{
	constexpr float gravity = 0.8f;
}

Object::Object(const Vector2& pos,const Vector2& vel) :
	m_pos(pos),
	m_velocity(vel),
	m_frame(0),
	m_sizeWidth(0),
	m_sizeHeight(0),
	m_handle(0)
{
	m_colRect.SetLT(m_pos.x, m_pos.y, m_sizeWidth, m_sizeHeight);
}

Object::~Object()
{
}

void Object::Gravity()
{
	m_velocity.y += gravity;
}