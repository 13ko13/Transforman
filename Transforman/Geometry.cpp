#include "Geometry.h"
#include <DxLib.h>
#include <cmath>

/// <summary>
/// ベクトルの大きさを計算する
/// </summary>
/// <returns>ベクトルの大きさ</returns>
float Vector2::Length() const
{
	return std::hypot(x, y);
}

void Vector2::Normalize()
{
	auto len = Length();
	if (len == 0.0f)
	{
		//0除算を避ける
		x == 0.0f;
		y == 0.0f;
		return;
	}

	//xとyをlenで割ることで正規化する
	x /= len;
	y /= len;

	
}
