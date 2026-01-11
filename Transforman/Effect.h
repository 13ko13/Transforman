#pragma once
#include "Utility/Geometry.h"

class Effect
{
public:
    Effect(const Vector2& pos);
	virtual ~Effect();
    virtual void Update();
    virtual void Draw();
	bool GetIsDead() const { return m_isDead; }
    const Vector2 GetPos() const { return m_pos; }

protected:
	Vector2 m_pos;
    bool m_isDead;
};

