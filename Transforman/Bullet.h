#pragma once
#include "Object.h"
#include <memory>

class Circle;
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

protected:
	Vector2 m_dir;
	bool m_isAlive;
	std::shared_ptr<Circle> m_pCircle;
};

