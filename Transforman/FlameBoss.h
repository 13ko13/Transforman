#pragma once
#include "Objects/EnemyBase.h"
#include <vector>
#include <memory>

/// <summary>
/// handleの要素数の列挙型
/// </summary>
enum class GraphNumber
{
	FlameBreath,
	FlameIdle,
};

class FlameBoss : public EnemyBase
{
public:
	FlameBoss(std::shared_ptr<Map> pMap);
    ~FlameBoss();

	void Init() override;
	void Update(GameContext& ctx) override;
	void Draw(std::shared_ptr<Camera> pCamera) override;

	/// <summary>
	/// プレイヤーが到着したときに呼び出される関数
	/// </summary>
	void OnArrive() override;

	/// <summary>
	/// ダメージを受けたときに呼び出される関数
	/// </summary>
	void OnDamage() override;

private:
	/// <summary>
	/// 攻撃行動を行う関数
	/// </summary>
	void Attack() override;

private:
	std::vector<int> m_handles; //画像ハンドルの配列
};

