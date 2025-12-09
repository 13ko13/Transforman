#pragma once
#include "Object.h"
#include "../Charactor.h"
#include <memory>
#include "../Collider/Rect.h"
#include <vector>

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
private:

protected:
	int m_appearTime;//出現中のタイム計測
	bool m_isAppear;//自分が出現しているかどうか

	enum class State
	{
		Appear,
		Idle,
		Rush,
		Shot,
	};
	State m_state;//状態
};

