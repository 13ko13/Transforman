#pragma once
#include "Object.h"
class Bullet : public Object
{
	Bullet();
	~Bullet();

	void Init() override;
	void Update() override;
	void Draw() override;
};

