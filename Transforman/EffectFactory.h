#pragma once
#include <vector>
#include "Utility/Geometry.h"
#include <list>
#include <memory>

enum class EffectType
{
	SmallExplosion,
	LargeExplosion,
	NumEffectType
};

class Effect;
class EffectFactory
{
private:
	std::vector<int> m_handles;//エフェクトの画像ハンドル
	std::list<std::shared_ptr<Effect>> m_effects;//エフェクトのリスト

public:
	EffectFactory();
	void Create(const Vector2& pos, EffectType type);
	void Update();
	void Draw();
};

