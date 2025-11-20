#pragma once
#include "Geometry.h"
#include <memory>

class Rect;
class Camera;
class Circle
{
public:
	Circle();
	~Circle();

	void Draw(Camera& camera);
	void SetPos(const Vector2& pos) { m_pos = pos; }
	/// <summary>
	/// ’†SŠÔ‹——£‚ğ‹‚ß‚é
	/// </summary>
	/// <returns>’†S‹——£</returns>
	float GetDistance(Vector2& pos);

	/// <summary>
	/// ‰~‚Æ‹éŒ`‚Ì“–‚½‚è”»’è
	/// </summary>
	/// <returns>‹éŒ`‚Æ“–‚½‚Á‚Ä‚¢‚é:true,“–‚½‚Á‚Ä‚¢‚È‚¢:false</returns>
	bool IsCollWithRect(const Rect& rect);

	/// <summary>
	/// •`‰æ‚·‚éÛ‚É”¼Œa‚ğŒˆ‚ß‚é
	/// </summary>
	/// <param name="radius">”¼Œa</param>
	void SetRadius(float radius) { m_radius = radius; }
private:
	Vector2 m_pos;
	float m_radius;
};

