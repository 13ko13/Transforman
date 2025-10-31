#pragma once
#include "Object.h"
class Player : public Object
{
public:
	Player();
	~Player();

	void Init() override;
	void Update() override;
	void Draw() override;

private:
	int m_handle;	//‰æ‘œƒnƒ“ƒhƒ‹
};

