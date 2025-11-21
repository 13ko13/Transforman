#include "Bullet.h"
#include "Camera.h"
#include "Circle.h"

Bullet::Bullet() :
	Object({ 0.0f,0.0f }, { 0.0f,0.0f }),
	m_isAlive(false),
	m_dir({ 0.0f,0.0f })
{
	//“–‚½‚è”»’è‚ğ’†S‚Éİ’è‚·‚é
	m_circle.SetPos(m_pos);
}

Bullet::~Bullet()
{

}

void Bullet::Init()
{

}

void Bullet::Update()
{

}

void Bullet::Draw(Camera camera)
{

}