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

	void DirUpUpdate();
	void DirDownUpdate();
	using UpdateFunc_t = void(EnemyBullet::*)();
	UpdateFunc_t m_update;

	void DirUpDraw();
	void DirDownDraw();
	using DrawFunc_t = void(EnemyBullet::*)();	
	DrawFunc_t m_draw;

	void SetDirection(Direction direction) { m_direction = direction; }

private:
	Direction m_direction;
};

