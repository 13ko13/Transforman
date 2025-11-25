#pragma once
#include "Bullet.h"
#include "Input.h"
#include <memory>
#include "Geometry.h"
#include "Rect.h"


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
	void Update(GameContext& ctx) override;
	void Draw(Camera camera) override;

	void SetIsRight(bool isRight) { m_isRight = isRight; }
	void SetType(BulletType bulletType) { m_bulletType = bulletType; }

private:
	bool m_isRight;
	BulletType m_bulletType;
	Rect m_rect;
};
