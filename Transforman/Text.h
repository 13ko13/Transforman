#pragma once
#include "Utility/Geometry.h"

class Text
{
public:
	Text(int handle);
	~Text();
	void Update();
	void Draw();
private:
	Vector2 m_pos;//ˆÊ’u
	int m_handle;//‰æ‘œƒnƒ“ƒhƒ‹
};