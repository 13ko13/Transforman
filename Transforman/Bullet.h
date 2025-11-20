#pragma once
#include "Object.h"
#include <memory>
#include "Circle.h"

class Bullet : public Object
{
public:
	Bullet();
	virtual ~Bullet();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw(Camera camera) override;

	Vector2 GetPos() { return m_pos; }
	void SetPos(const Vector2& pos) { m_pos = pos; }
	bool GetIsAlive() { return m_isAlive; }
	void SetIsAlive(bool isAlive) { m_isAlive = isAlive; }

	Circle GetCircle() const { return m_circle; }

protected:
	Vector2 m_dir;
	bool m_isAlive;
	Circle m_circle;
};

