#pragma once
#include <vector>
#include "UserInterface.h"

class EnemyHpBar : public UserInterface
{
public:
	EnemyHpBar(int maxHP);
	~EnemyHpBar();
	
	void Update(int currentHP);
	void Update() override;
	void Draw() override;
private:
	enum class HandleNomber
	{
		Frame,//枠
		Heart,//ハート
		Normal,//通常HP
		Pinch,//ピンチ時
		Empty,//空HP
	};

	int m_maxHP;
	int m_currentHP;
	std::vector<int> m_handles;//ヒットポイントの画像ハンドル
};

