#pragma once
#include "Geometry.h"
#include "Rect.h"

class Object
{
public:
	Object(const Vector2& pos,const Vector2& vel);
	virtual ~Object();

	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Draw() abstract;

	/// <summary>
	/// d—Í‚ğŒvZ‚·‚éŠÖ”
	/// </summary>
	void Gravity();

	Rect GetColRect() const { return m_colRect; }

protected:
	float m_frame;

	Vector2 m_pos;
	Vector2 m_velocity;

	//“–‚½‚è”»’è
	Rect m_colRect;
};

