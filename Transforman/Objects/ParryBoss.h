#pragma once
#include "EnemyBase.h"
class ParryBoss : public EnemyBase
{
public:
	ParryBoss(std::shared_ptr<Map> pMap);
	~ParryBoss();

	void Update();
	void Draw();

private:

};

