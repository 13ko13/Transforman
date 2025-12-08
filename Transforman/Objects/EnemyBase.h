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
	EnemyBase(int width,int height,std::shared_ptr<Map> pMap);
	virtual ~EnemyBase();

	virtual void Init() override;
	virtual void Update(GameContext& ctx) override;
	virtual void Draw(std::shared_ptr<Camera> pCamera) override;

	virtual void Attack() abstract;
private:

protected:
};

