#pragma once
#include "Geometry.h"

class Object
{
public:
	Object(const Vector2& pos,const Vector2& dir);
	virtual ~Object();

	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Draw() abstract;

protected:
	Vector2 m_pos;
	Vector2 m_dir;
};

