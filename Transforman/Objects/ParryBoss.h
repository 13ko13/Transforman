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

	void IdleDraw(std::shared_ptr<Camera> pCamera);
	void ParryDraw(std::shared_ptr<Camera> pCamera);
	void JumpingDraw(std::shared_ptr<Camera> pCamera);
	void FallAttackDraw(std::shared_ptr<Camera> pCamera);
	void IdleUpdate(GameContext& ctx);
	void ParryUpdate(GameContext& ctx);
	void JumpingUpdate(GameContext& ctx);
	void FallAttackUpdate(GameContext& ctx);

private:
	enum class State
	{
		None,//何もしない
		Appear,//出現
		Idle,//待機,
		Parry,//パリィ
		Jumping,//ジャンプ
		FallAttack,//落下攻撃
		
		StateNum
	};
	State m_state;//状態

	Animation m_idleAnim; 
	Animation m_parryAnim;
	Animation m_jumpAnim;
	Animation m_fallAttackAnim;

	int m_moveCooldown;//次の行動までのフレーム数

	int m_jumpFrame;//ジャンプ中のフレーム数
	Vector2 m_playerPrevPos;//プレイヤーの前フレームの位置
};