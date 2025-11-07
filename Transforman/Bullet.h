#pragma once
#include "Object.h"
class Bullet : public Object
{
public:
	Bullet();
	virtual ~Bullet();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

	Vector2 GetPos() { return m_pos; }
	void SetPos(const Vector2& pos) { m_pos = pos; }
	bool GetIsAlive() { return m_isAlive; }
	void SetIsAlive(bool isAlive) { m_isAlive = isAlive; }

protected:
	Vector2 m_dir;
	bool m_isAlive;
};

