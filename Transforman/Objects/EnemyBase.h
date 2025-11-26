#pragma once
#include "Object.h"
#include <memory>
#include "../Collider/Rect.h"
#include <vector>

// プロトタイプ宣言
class Player;
struct GameContext;
/// <summary>
/// エネミー全体の基底クラス
/// </summary>
class EnemyBase : public Object
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Init() override abstract;
	virtual void Update(GameContext& ctx) override abstract;
	virtual void Draw(Camera camera) override abstract;

	virtual void Attack() abstract;

	/// <summary>
	/// 矩形の参照を返す
	/// </summary>
	/// <returns>矩形のポインタ</returns>
	const Rect& GetColRect() const { return m_colRect; }

	const bool GetIsDead() const { return m_isDead; }
	void SetIsDead(bool isDead) { m_isDead = isDead; }

private:

protected:
	Rect m_colRect;
	bool m_isDead;

};

