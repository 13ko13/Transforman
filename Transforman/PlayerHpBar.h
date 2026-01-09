#pragma once
#include "UserInterface.h"
#include "Objects/Player.h"
#include <memory>
#include <vector>

class PlayerHpBar : public UserInterface
{
public:
	PlayerHpBar(int maxHitPoint);
	~PlayerHpBar();

	void Update() override;
	void Update(std::shared_ptr<Player> pPlayer);
	void Draw() override;

private:
	enum class handleNomber
	{
		Frame,//枠
		Background,//背景
		Heart,//ハート
		Normal,//通常HP
		Pinch,//ピンチ時
		Empty,//空HP
	};
	std::vector<int> m_handles;//ヒットポイントの画像ハンドル
	int m_hitPoint;//現在のHP
	int m_maxHitPoint;//最大HP
};

