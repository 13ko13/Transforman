#pragma once
#include "Object.h"
#include "../Charactor.h"
#include <memory>
#include "../Collider/Rect.h"
#include <vector>
#include "../Graphics/Animation.h"

// プロトタイプ宣言
class Player;
struct GameContext;
/// <summary>
/// エネミー全体の基底クラス
/// </summary>
class EnemyBase : public Charactor
{
public:
	EnemyBase(int width,int height,std::shared_ptr<Map> pMap);
	virtual ~EnemyBase();

	virtual void Init() override;
	virtual void Update(GameContext& ctx) override;
	virtual void Draw(std::shared_ptr<Camera> pCamera) override;

	virtual void Attack() abstract;
	virtual void OnArrive() abstract;
	/// <summary>
	/// ボス戦が始まっているかどうかを返す関数
	/// </summary>
	/// <returns>true:始まっている,false:始まっていない</returns>
	bool GetIsStart() { return m_isStart; }

	/// <summary>
	/// 現在のチャージショットボスのステートを取得する
	/// </summary>
	/// <returns>チャージショットボスのステート</returns>
	const int GetState() const { return static_cast<int>(m_state); }
private:
	
protected:
	enum class State
	{
		None,//何もしない
		Appear,//出現
		Idle,//待機
	};
	State m_state;//状態
	int m_appearTime;//出現中のタイム計測
	bool m_isAppear;//自分が出現しているかどうか
	bool m_isStart;//ボス戦が始まっているかどうか
	Animation m_idleAnim;

protected:
	/// <summary>
	/// ボス出現中の関数
	/// </summary>
	virtual void AppearUpdate() abstract;
	/// <summary>
	/// アイドル状態の関数
	/// </summary>
	/// <param name="ctx">オブジェクトクラスを継承しているオブジェクトの構造体</param>
	virtual void IdleUpdate(GameContext& ctx) abstract;

	/// <summary>
	/// 何もない状態の更新関数
	/// </summary>
	virtual void NoneUpdate() abstract;
};

