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
	void Update(std::vector<std::shared_ptr<EnemyBullet>>& pBullets);
	void Draw(Camera camera) override;

	void Attack() override;
	void Attack(std::vector<std::shared_ptr<EnemyBullet>>& pBullets);
	

private:
	bool m_isRight;
	int m_attackCooltime;
	std::shared_ptr<Player> m_pPlayer;
};

