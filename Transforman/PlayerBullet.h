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

class PlayerBullet : public Bullet
{
public:
	PlayerBullet();
	~PlayerBullet();

	void Init() override;
	void Update() override;
	void Draw() override;

	void SetIsRight(bool isRight) { m_isRight = isRight; }
	void SetType(BulletType bulletType) { m_bulletType = bulletType; }

private:
	bool m_isRight;
	BulletType m_bulletType;
};
