#include "Geometry.h"
#include <DxLib.h>
#include <cmath>

/// <summary>
/// �x�N�g���̑傫�����v�Z����
/// </summary>
/// <returns>�x�N�g���̑傫��</returns>
float Vector2::Length() const
{
	return std::hypot(x, y);
}

void Vector2::Normalize()
{
	auto len = Length();
	if (len == 0.0f)
	{
		//0���Z�������
		x == 0.0f;
		y == 0.0f;
		return;
	}

	//x��y��len�Ŋ��邱�ƂŐ��K������
	x /= len;
	y /= len;

	
}
