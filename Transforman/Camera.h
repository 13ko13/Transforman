#pragma once
#include "Geometry.h"

class Player;
class Camera
{
public:
	Camera();
	~Camera();

	void Update(const Player& player);

	const Vector2& GetDrawOffset() const { return m_drawOffset; };
	Vector2 VLerp(const Vector2& start, const Vector2& end, float t);

private:
	Vector2 m_pos;	//実際のカメラのポジション
	Vector2 m_drawOffset;	//全てのDrawObjectに足す値
};

