#pragma once
#include "Object.h"
#include "Input.h"
#include <memory>
#include "Geometry.h"

class Player;

class Bullet : public Object
{
public:
	Bullet();
	~Bullet();

	void Init() override;
	void Update() override;
	void Draw() override;

	void SetPos(const Vector2& pos) { m_pos = pos; }
	bool GetIsAlive() const { return m_isAlive; }
	void SetIsAlive(bool isAlive) { m_isAlive = isAlive; }
	void SetIsRight(bool isRight) { m_isRight = isRight; }

private:
	Vector2 m_dir;
	bool m_isAlive;
	bool m_isRight;

	std::shared_ptr<Player> m_pPlayer;
};

