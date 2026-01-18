#include "EffectFactory.h"
#include "Effect.h"
#include "RushEffect.h"
#include "HitWallEffect.h"
#include "PosProvider.h"
#include <DxLib.h>
#include <cassert>
#include "Graphics/Camera.h"

EffectFactory::EffectFactory()
{
	int handle = -1;

	//エフェクト画像の読み込み
	//ラッシュエフェクト
	handle = LoadGraph("img/game/Effect/chargeboss_rush_effect.png");
	assert(handle >= 0);
	m_handles.push_back(handle);

	//壁衝突エフェクト
	handle = LoadGraph("img/game/Effect/chargeboss_hit_wall_effect.png");
	assert(handle >= 0);
	m_handles.push_back(handle);
}

std::weak_ptr<Effect> EffectFactory::Create(const Vector2& pos, EffectType type)
{
	std::shared_ptr<Effect> effect;//戻り値用エフェクトポインタ

	switch (type)
	{
	case EffectType::rush:
		//ラッシュエフェクトの生成
		effect = std::make_shared<RushEffect>(
			m_handles[static_cast<int>(EffectType::rush)], pos);
		break;
	case EffectType::hitWall:
		//壁衝突エフェクトの生成
		effect = std::make_shared<HitWallEffect>(
			m_handles[static_cast<int>(EffectType::hitWall)], pos);
		break;
	}

	if (effect) m_effects.push_back(effect);
	return effect;
}

std::weak_ptr<Effect> EffectFactory::CreateFollow(
	std::shared_ptr<PosProvider> target,
	EffectType type, const Vector2& offset)
{
	std::shared_ptr<Effect> effect;
	switch (type)
	{
	case EffectType::rush:
		{
		//ラッシュエフェクトの生成
		effect = std::make_shared<RushEffect>(
			m_handles[static_cast<int>(EffectType::rush)],
			target, offset);
		break;
		}
	}

	if (effect) m_effects.push_back(effect);
	return effect;
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
