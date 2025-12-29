#pragma once
#include "EnemyBase.h"

class Animation;
class ParryBoss : public EnemyBase
{
public:
	ParryBoss(std::shared_ptr<Map> pMap);
	~ParryBoss();

	void Init() override;
	void Update(GameContext& ctx) override;
	void Draw(std::shared_ptr<Camera> pCamera) override;

	/// <summary>
	/// プレイヤーが到着したときに呼び出される関数
	/// </summary>
	void OnArrive() override;
private:
	/// <summary>
	/// 攻撃行動を行う関数
	/// </summary>
	void Attack() override;

private:
	enum class State
	{
		None,//何もしない
		Appear,//出現
		Idle,//待機,

		StateNum
	};
	State m_state;//状態

	Animation m_idleAnim; 
};

