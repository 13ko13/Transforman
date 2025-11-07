#pragma once
#include "EnemyBase.h"
#include <vector>
#include <memory>

class PlayerBullet;
class ScrewDriver : public EnemyBase
{
public:
	ScrewDriver();
	~ScrewDriver();

	void Init() override;
	void Update() override;
	void Draw() override;

	void Attack() override;

private:
	std::vector<std::shared_ptr<PlayerBullet>> m_pBullets;
};

