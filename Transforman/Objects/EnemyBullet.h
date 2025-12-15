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
class Player;
class EnemyBullet : public Bullet
{
public:
	EnemyBullet();
	~EnemyBullet();

	void Init() override;
	void Update(GameContext& ctx) override;
	void Draw(std::shared_ptr<Camera> pCamera) override;	

	/// <summary>
	/// 方向ベクトルを設定します。
	/// </summary>
	/// <param name="dir">設定する方向ベクトル。</param>
	void SetDir(const Vector2& dir) { m_dir = dir; }
private:
	//変数
	EnemyState m_state;

	//関数
	/// <summary>
	/// 弾自身の移動
	/// </summary>
	void Movement();
};

