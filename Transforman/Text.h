#pragma once
#include "Utility/Geometry.h"

enum class TextType
{
	Move,
	Jump,
	Shot,
	ChargeShot,
	Flame,
	Parry
};

class Text
{
public:
	Text(TextType textType);
	~Text();
	void Update();
	void Draw();
private:
	Vector2 m_pos;//位置
	int handle;//画像ハンドル

	TextType m_type;//どのテキスト(画像)を表示させるか
};