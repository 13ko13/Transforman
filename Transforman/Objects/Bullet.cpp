#include "Bullet.h"
#include "../Graphics/Camera.h"
#include "../Collider/Circle.h"

Bullet::Bullet() :
	Object({ 0.0f,0.0f }, { 0.0f,0.0f }),
	m_isAlive(false),
	m_dir({ 0.0f,0.0f })
{
	
}

Bullet::~Bullet()
{

}

void Bullet::Init()
{

}

void Bullet::Update(GameContext&)
{

}

void Bullet::Draw(std::shared_ptr<Camera> pCamera)
{

}