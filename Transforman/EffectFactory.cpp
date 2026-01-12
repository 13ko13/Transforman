#include "EffectFactory.h"
#include "Effect.h"
#include <DxLib.h>
#include <cassert>

EffectFactory::EffectFactory()
{
	int handle = -1;
	m_handles.push_back(handle);//ダミー

	handle = LoadGraph("Resources/Effects/SmallExplosion.png");
	assert(handle >= 0);
	m_handles.push_back(handle);

	handle = LoadGraph("Resources/Effects/LargeExplosion.png");
	assert(handle >= 0);
	m_handles.push_back(handle);

	handle = LoadGraph("Resources/Effects/Smoke.png");
	assert(handle >= 0);
	m_handles.push_back(handle);
}

void EffectFactory::Create(const Vector2& pos, EffectType type)
{
}

void EffectFactory::Update()
{
	//for(auto& effect : m_effects)
	//{
	//	effect->Update();
	//}
	//m_effects.remove_if([](const std::shared_ptr<Effect>& effect)
	//{
	//	//Todo:エフェクトが死んでいるかどうかを判定して返す
	//});
}

void EffectFactory::Draw()
{
	/*for(auto& effect : m_effects)
	{
		effect->Draw();
	}*/
}
