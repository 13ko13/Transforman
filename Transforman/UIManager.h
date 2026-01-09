#pragma once
#include <memory>
#include "HpBar.h"

class Player;
class UIManager
{
public:
	UIManager(std::shared_ptr<Player> pPlayer);
	~UIManager();

	void Update();
	void Draw();

private:
	std::shared_ptr<HpBar> playerHpBar;
};

