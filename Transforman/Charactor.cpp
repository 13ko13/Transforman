#include "Charactor.h"
#include "Graphics/Camera.h"
#include "Map.h"

Charactor::Charactor() : 
	Object({ 0.0f,0.0f }, { 0.0f,0.0f }),
	m_isGround(false),
	m_isRight(false),
	m_isDead(false)
{
	m_pMap = std::make_shared<Map>();
}

Charactor::~Charactor()
{

}

void Charactor::Init()
{
}

void Charactor::Update(GameContext& ctx)
{
}

void Charactor::Draw(Camera camera)
{
}

void Charactor::HitMap()
{
	//c•ûŒü‚ÌÕ“Ë
	
}
