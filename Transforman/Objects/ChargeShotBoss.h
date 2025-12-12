#pragma once
#include "EnemyBase.h"
#include <vector>
#include <memory>

class EnemyBullet;
class Player;
class ChargeShotBoss : public EnemyBase
{
public:
	ChargeShotBoss(std::shared_ptr<Map> pMap);
	~ChargeShotBoss();

	void Init() override;
	void Update(GameContext& ctx) override;
	void Draw(std::shared_ptr<Camera> pCamera) override;

	void Attack() override;
	void Attack(std::vector<std::shared_ptr<EnemyBullet>>& pBullets,
				std::shared_ptr<Player> pPlayer);
	void OnArrive() override;

private:
	int m_attackCoolTime;//攻撃までのクールタイム
	bool m_isRushing;
};

