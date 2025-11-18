#pragma once
#include "Object.h"
#include <memory>

// プロトタイプ宣言
class Player;
/// <summary>
/// エネミー全体の基底クラス
/// </summary>
class EnemyBase : public Object
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Init() override abstract;
	virtual void Update() override abstract;
	virtual void Draw(Camera camera) override abstract;

	virtual void Attack() abstract;
	void SetPlayerPtr(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }
private:

protected:
	std::shared_ptr<Player> m_pPlayer;
};

