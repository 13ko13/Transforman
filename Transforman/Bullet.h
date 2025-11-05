#pragma once
#include "Object.h"
#include "Input.h"

class Bullet : public Object
{
	Bullet();
	~Bullet();

	void Init() override;
	void Draw() override;
	void Update(Input& input);
	void Draw() override;
};

