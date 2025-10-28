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

Vector2 Vector2::Normalized() const
{
	auto len = Length();
	if (len == 0.0f)
	{
		//0���Z�������
		return { 0.0f,0.0f };
	}
	return { x / len, y / len };
}

Vector2 Vector2::operator-() const
{
	/// �x�N�g���𔽓]�����x�N�g����Ԃ�
	return { -x,-y };
}

void Vector2::operator+=(const Vector2& val)
{
	/// �x�N�g���̉��Z
	x += val.x;
	y += val.y;
}

void Vector2::operator-=(const Vector2& val)
{
	/// �x�N�g���̌��Z
	x -= val.x;
	y -= val.y;
}

void Vector2::operator*=(const float scale)
{
	/// �x�N�g���̃X�J���[�{
	x *= scale;
	y *= scale;
}

Vector2 Vector2::operator+(const Vector2& val) const
{
	/// �x�N�g���̉��Z
	return { x + val.x, y + val.y };
}

Vector2 Vector2::operator-(const Vector2& val) const
{
	/// �x�N�g���̌��Z
	return { x - val.x, y - val.y };
}

Vector2 Vector2::operator*(float scale) const
{
	/// �x�N�g���̃X�J���[�{
	return { x * scale, y * scale };
}

void Circle::Draw()
{
	DrawCircleAA(pos.x, pos.y, r, 16, 0xffffff, false);
}