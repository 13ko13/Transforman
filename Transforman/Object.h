#pragma once
#include "Geometry.h"

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

protected:
	Vector2 m_pos;
	Vector2 m_velocity;

};

