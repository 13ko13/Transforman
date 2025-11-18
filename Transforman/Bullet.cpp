#include "Bullet.h"
#include "Camera.h"
#include "Circle.h"

Bullet::Bullet() :
	Object({ 0.0f,0.0f }, { 0.0f,0.0f }),
	m_isAlive(false),
	m_dir({ 0.0f,0.0f })
{
	m_pCircle = std::make_shared<Circle>();
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