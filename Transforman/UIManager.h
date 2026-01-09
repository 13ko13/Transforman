#pragma once
#include <memory>
#include "PlayerHpBar.h"

class Player;
class UIManager
{
public:
	UIManager(std::shared_ptr<Player> pPlayer);
	~UIManager();

	void Update(std::shared_ptr<Player> pPlayer);
	void Draw();

private:
	std::shared_ptr<PlayerHpBar> playerHpBar;
};

