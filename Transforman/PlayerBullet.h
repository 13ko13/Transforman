#pragma once
#include "Bullet.h"
#include "Input.h"
#include <memory>
#include "Geometry.h"

enum class BulletType
{
	Normal,
	Charge,
	Fire
};

class EnemyBase;
class PlayerBullet : public Bullet
{
public:
	PlayerBullet();
	~PlayerBullet();

	void Init() override;
	void Update() override;
	void Draw(Camera camera) override;

	void SetIsRight(bool isRight) { m_isRight = isRight; }
	void SetType(BulletType bulletType) { m_bulletType = bulletType; }
	void SetEnemy(std::shared_ptr<EnemyBase> pEnemy) { m_pEnemy = pEnemy; }

private:
	bool m_isRight;
	BulletType m_bulletType;
	std::shared_ptr<EnemyBase> m_pEnemy;
};
