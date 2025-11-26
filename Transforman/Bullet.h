#pragma once
#include "Object.h"
#include <memory>
#include "Circle.h"

struct GameContext;
class Bullet : public Object
{
public:
	Bullet();
	virtual ~Bullet();

	virtual void Init() override;
	virtual void Update(GameContext& ctx) override;
	virtual void Draw(Camera camera) override;

	const Vector2& GetPos() const { return m_pos; }
	void SetPos(const Vector2& pos) { m_pos = pos; }
	const bool GetIsAlive() const { return m_isAlive; }
	void SetIsAlive(bool isAlive) { m_isAlive = isAlive; }

	const Circle& GetCircle() const { return m_circle; }

protected:
	Vector2 m_dir;
	bool m_isAlive;
	Circle m_circle;
};

