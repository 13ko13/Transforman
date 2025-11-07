#pragma once
#include "Bullet.h"

/// <summary>
/// ’e‚Ì•ûŒü‚ð•\‚·—ñ‹“Œ^
/// </summary>
enum class Direction
{
	Up,
	Down
};

class EnemyBullet : public Bullet
{
public:
	EnemyBullet();
	~EnemyBullet();

	void Init() override;
	void Update() override;
	void Draw() override;

private:
	Direction m_direction;
};

