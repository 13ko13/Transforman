#include "Object.h"

namespace
{
	constexpr float gravity = 0.98f;
}

Object::Object(const Vector2& pos,const Vector2& vel) :
	m_pos(pos),
	m_velocity(vel)
{

}

Object::~Object()
{
}

void Object::Gravity()
{
	m_velocity.y += gravity;
}
