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

private:
	Vector2 m_dir;
	bool m_isAlive;

	std::shared_ptr<Player> m_pPlayer;
};

