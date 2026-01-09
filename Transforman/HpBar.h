#pragma once
#include "UserInterface.h"
#include "Objects/Player.h"
#include <memory>
#include <vector>

class HpBar : public UserInterface
{
public:
	HpBar(int maxHitPoint,int srcX, int srcY);
	~HpBar();

	void Update() override;
	void Update(std::shared_ptr<Player> pPlayer);
	void Draw() override;

private:
	enum class handleNomber
	{
		Frame,//枠
		Background,//背景
		Normal,//通常HP
		pinch//ピンチ時
	};
	std::vector<int> m_handles;//ヒットポイントの画像ハンドル
	int m_hitPoint;//現在のHP
	int m_maxHitPoint;//最大HP
	int m_srcX;//横切り取りサイズ
	int m_srcY;//縦切り取りサイズ
};

