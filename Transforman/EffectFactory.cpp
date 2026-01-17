#include "EffectFactory.h"
#include "Effect.h"
#include "RushEffect.h"
#include "PosProvider.h"
#include <DxLib.h>
#include <cassert>
#include "Graphics/Camera.h"

EffectFactory::EffectFactory()
{
	int handle = -1;

	//エフェクト画像の読み込み
	handle = LoadGraph("img/game/Effect/chargeboss_rush_effect.png");
	assert(handle >= 0);
	m_handles.push_back(handle);
}

void EffectFactory::Create(const Vector2& pos, EffectType type)
{
	switch (type)
	{
	case EffectType::rush:
		//ラッシュエフェクトの生成
		m_effects.push_back(std::make_shared<RushEffect>(
			m_handles[static_cast<int>(EffectType::rush)], pos));
		break;
	}
}

void EffectFactory::CreateFollow(std::shared_ptr<PosProvider> target, EffectType type, const Vector2& offset)
{
	switch (type)
	{
	case EffectType::rush:
		{
		//ラッシュエフェクトの生成
		m_effects.push_back(std::make_shared<RushEffect>(
			m_handles[static_cast<int>(EffectType::rush)],
			target, offset));
		break;
		}
	}
}

void EffectFactory::Update()
{
	for (auto& effect : m_effects)
	{
		effect->Update();
	}
	m_effects.remove_if([](std::shared_ptr<Effect> effect)
		{
			return effect->GetIsDead();
		});
}

void EffectFactory::Draw(const std::shared_ptr<Camera>& pCamera)
{
	for (auto& effect : m_effects)
	{
		effect->Draw(pCamera);
	}
}
