#pragma once
#include "Object.h"

enum class State
{
	Idle,
	Shot,
	Jumpm,
	BigShot,
	Cutter,
	Bomb
};

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

