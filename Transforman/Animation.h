#pragma once
#include <memory>

class Player;
class Animation
{
public:
	Animation();
	~Animation();

	void Init();
	void Update();
	void Draw();

private:
	std::shared_ptr<Player> m_pPlayer;
};

