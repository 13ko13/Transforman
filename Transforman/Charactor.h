#pragma once
#include "Objects/Object.h"
#include "Collider/Rect.h"
#include <memory>

struct GameContext;
class Map;
class Charactor :public Object
{
public:
	Charactor(int width,int height,std::shared_ptr<Map> pMap);
	virtual ~Charactor();
	virtual void Init() override;
	virtual void Update(GameContext& ctx) override;
	virtual void Draw(std::shared_ptr<Camera> pCamera) override;
	/// <summary>
	/// マップチップと当たっていた時の処理
	/// </summary>
	virtual void HitMap(Rect& chipRect);
	/// <summary>
	/// 右向きか左向きかを設定する
	/// </summary>
	/// <param name="isRight">true:右向き,false:左向き</param>
	virtual void SetIsRight(bool isRight) { m_isRight = isRight; }
	/// <summary>
	/// 矩形の参照を返す
	/// </summary>
	/// <returns>参照された矩形</returns>
	virtual const Rect& GetColRect() const { return m_colRect; }

	/// <summary>
	/// キャラクターが死亡しているかどうかを返す
	/// </summary>
	/// <returns>死んでいる:true,生きている:false</returns>
	virtual const bool GetIsDead() const { return m_isDead; }
	/// <summary>
	/// キャラクターを死亡させる
	/// </summary>
	/// <param name="isDead">死ぬかどうか</param>
	virtual void SetIsDead(bool isDead) { m_isDead = isDead; }
	/// <summary>
	/// キャラクターがどちらを向いているかを返す
	/// </summary>
	/// <returns>true:右,false:左</returns>
	virtual const bool GetIsRight() const { return m_isRight; }

private:

protected:
	Rect m_colRect;
	std::shared_ptr<Map> m_pMap;
	bool m_isDead;//死亡しているかどうか
	bool m_isGround;//接地しているかどうか
	bool m_isRight;//右を向いているかどうか

	int m_width;//キャラクターの幅
	int m_height;//キャラクターの高さ
};