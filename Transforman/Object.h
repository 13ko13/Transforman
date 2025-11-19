#pragma once
#include "Geometry.h"
#include <memory>

class Camera;
class Object
{
public:
	Object(const Vector2& pos,const Vector2& vel);
	virtual ~Object();

	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Draw(Camera camera) abstract;

	/// <summary>
	/// 重力を計算する関数
	/// </summary>
	void Gravity();

	Vector2 GetPos() const { return m_pos; }

protected:
	int m_handle;	//画像のハンドル
	int m_frame;
	int m_sizeWidth;
	int m_sizeHeight;

	Vector2 m_pos;
	Vector2 m_velocity;
};

