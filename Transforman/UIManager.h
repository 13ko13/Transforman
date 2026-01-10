#pragma once
#include <memory>

class Player;
class PlayerHpBar;
class EnemyHpBar;
class ChargeShotBoss;
class UIManager
{
public:
	UIManager(std::shared_ptr<Player> pPlayer, std::shared_ptr<ChargeShotBoss> pChargeBoss);
	~UIManager();

	void Update(std::shared_ptr<Player> pPlayer, std::shared_ptr<ChargeShotBoss> pChargeBoss);
	void Draw();

private:
	std::shared_ptr<PlayerHpBar> playerHpBar;
	std::shared_ptr<EnemyHpBar> enemyHpBar;	
};

