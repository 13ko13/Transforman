#pragma once
#include "EnemyBase.h"
#include <vector>
#include <memory>

class EnemyBullet;
class Player;
class ChargeShotBoss : public EnemyBase
{
public:
	ChargeShotBoss();
	~ChargeShotBoss();

	void Init() override;
	void Update() override;
	void Draw() override;

	void Attack() override;
	void SetPlayerPtr(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }

private:
	bool m_isRight;

	std::vector<std::shared_ptr<EnemyBullet>> m_pBullets;
	int m_attackCooltime;
	std::shared_ptr<Player> m_pPlayer;
};

