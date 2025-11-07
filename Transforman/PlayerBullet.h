#pragma once
#include "Bullet.h"
#include "Input.h"
#include <memory>
#include "Geometry.h"

class PlayerBullet : public Bullet
{
public:
	PlayerBullet();
	~PlayerBullet();

	void Init() override;
	void Update() override;
	void Draw() override;

	void SetIsRight(bool isRight) { m_isRight = isRight; }

private:
	bool m_isRight;
};
