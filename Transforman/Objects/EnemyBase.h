#pragma once
#include "Object.h"
#include "../Charactor.h"
#include <memory>
#include "../Collider/Rect.h"
#include <vector>

// プロトタイプ宣言
class Player;
struct GameContext;
/// <summary>
/// エネミー全体の基底クラス
/// </summary>
class EnemyBase : public Charactor
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Init() override;
	virtual void Update(GameContext& ctx) override;
	virtual void Draw(Camera camera) override;

	virtual void Attack() abstract;
private:

protected:
};

