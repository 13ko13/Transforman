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
	void SetPlayerPtr(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }

	/// <summary>
	/// 矩形のポインタを返す
	/// </summary>
	/// <returns>矩形のポインタ</returns>
	std::shared_ptr<Rect> GetColRectPtr() { return m_pColRect; }
private:

protected:
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Rect> m_pColRect;

};

