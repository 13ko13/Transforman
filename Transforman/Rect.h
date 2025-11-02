#pragma once
#include "Geometry.h"

/// <summary>
/// 矩形を管理するクラス
/// </summary>
class Rect
{
public:
	Rect();

	~Rect();

	void Draw(unsigned int Color, bool isFill);

	void SetLT(float right, float top, float width, float height);

	void SetCenter(float x, float y, float width, float height);

	float GetWidth() const;

	float GetHeight() const;

	Vector2 GetCenter() const;

	float GetLeft() const { return m_left; }

	float GetRight() const { return m_right; }

	float GetTop() const { return m_top; }
	float GetBottom() const { return m_bottom; }

private:
	float m_left;  //左上のX座標
	float m_right; //右下のX座標
	float m_top;	   //左上のY座標
	float m_bottom;//右下のY座標
};

