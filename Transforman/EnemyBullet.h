#pragma once
#include "Bullet.h"
#include <memory>

enum class EnemyState
{
	Normal,
	Shotting,
	Dead
};

//プロトタイプ宣言
class ChargeShotBoss;

class EnemyBullet : public Bullet
{
public:
	EnemyBullet();
	~EnemyBullet();

	void Init() override;
	void Update() override;
	void Draw() override;

	/// <summary>
	/// 弾自身の移動
	/// </summary>
	void Movement();

	void SetDir(const Vector2& dir) { m_dir = dir; }
private:
	EnemyState m_state;
};

