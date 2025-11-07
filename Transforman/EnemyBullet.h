#pragma once
#include "Bullet.h"

class EnemyBullet : public Bullet
{
public:
	EnemyBullet();
	~EnemyBullet();

	void Init() override;
	void Update() override;
	void Draw() override;
};

