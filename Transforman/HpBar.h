#pragma once
#include "UserInterface.h"
class HpBar : public UserInterface
{
public:
	HpBar(int maxHitPoint);
	~HpBar();

	void Update() override;
	void Draw() override;

private:
	int m_hitPoint;//åªç›ÇÃHP
	int m_maxHitPoint;//ç≈ëÂHP
};

