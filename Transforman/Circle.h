#pragma once
#include "Geometry.h"

class Rect;
class Circle
{
public:
	Circle();
	~Circle();

	void Draw();	
	void SetPos(const Vector2& pos) { m_pos = pos; }
	/// <summary>
	/// 中心間距離を求める
	/// </summary>
	/// <returns>中心距離</returns>
	float GetDistance(Vector2& pos);

	/// <summary>
	/// 円と矩形の当たり判定
	/// </summary>
	/// <returns>矩形と当たっている:true,当たっていない:false</returns>
	bool IsCollWithRect(Rect& rect);
private:
	Vector2 m_pos;
	float m_radius;
};

