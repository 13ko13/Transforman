#pragma once
#include "Geometry.h"
#include "Rect.h"

class Object
{
public:
	Object(const Vector2& pos,const Vector2& vel);
	virtual ~Object();

	virtual void Init() abstract;
	virtual void Update() abstract;
	virtual void Draw() abstract;

	/// <summary>
	/// 重力を計算する関数
	/// </summary>
	void Gravity();

	/// <summary>
	/// オブジェクトの衝突判定用の矩形を返す
	/// </summary>
	/// <returns>矩形</returns>
	Rect GetColRect() const { return m_colRect; }

	Vector2 GetPos() const { return m_pos; }

protected:
	int m_handle;	//画像のハンドル
	int m_frame;
	int m_sizeWidth;
	int m_sizeHeight;

	Vector2 m_pos;
	Vector2 m_velocity;

	//当たり判定
	Rect m_colRect;
};

