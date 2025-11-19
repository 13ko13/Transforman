#pragma once
#include "Object.h"
#include <memory>
#include "Rect.h"

// プロトタイプ宣言
class Player;
/// <summary>
/// エネミー全体の基底クラス
/// </summary>
class EnemyBase : public Object
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Init() override abstract;
	virtual void Update() override abstract;
	virtual void Draw(Camera camera) override abstract;

	virtual void Attack() abstract;

	/// <summary>
	/// 矩形のポインタを返す
	/// </summary>
	/// <returns>矩形のポインタ</returns>
	std::shared_ptr<Rect> GetColRectPtr() { return m_pColRect; }

	bool GetIsDead() const { return m_isDead; }
	void SetIsDead(bool isDead) { m_isDead = isDead; }

private:

protected:
	std::shared_ptr<Rect> m_pColRect;
	bool m_isDead;

};

