#pragma once
#include "EnemyBase.h"
#include <vector>
#include <memory>

class EnemyBullet;
class Player;
class ChargeShotBoss : public EnemyBase
{
public:
	ChargeShotBoss(std::shared_ptr<Map> pMap);
	~ChargeShotBoss();

	void Init() override;
	void Update(GameContext& ctx) override;
	void Draw(std::shared_ptr<Camera> pCamera) override;
	
	/// <summary>
	/// プレイヤーが到着したときに呼び出される関数
	/// </summary>
	void OnArrive() override;
	
private:
	int m_GroundNum;//地面に触れた回数
	int m_prevRushTime;//突進準備中の現在のフレーム数
	bool m_isRushing;//突進中かどうか
	int m_actionCooldown;//次の行動までのフレーム数

	Animation m_rushAnim;
	Animation m_prevRushAnim;
	Animation m_shotAnim;

	enum class ChargeShotBossState
	{
		None,//何もしない
		PrevRush,//突進準備
		Rush,//突進
		Shot,//弾

		StateMax//状態の最大数
	};
	ChargeShotBossState m_chargeBossState;

private:
	void Attack() override;
	/// <summary>
	/// 敵の行動を決める関数
	/// </summary>
	/// <param name="pBullets">敵弾の配列のポインタ</param>
	/// <param name="pPlayer">プレイヤーのポインタ</param>
	void Attack(std::vector<std::shared_ptr<EnemyBullet>>& pBullets,
		std::shared_ptr<Player> pPlayer);
	/// <summary>
	/// 敵が弾を撃ったときの関数
	/// </summary>
	/// <param name="pBullets"></param>
	/// <param name="pPlayer"></param>
	void ShotUpdate(std::vector<std::shared_ptr<EnemyBullet>>& pBullets,
		std::shared_ptr<Player> pPlayer);
	/// <summary>
	/// 敵が突進した時の関数
	/// </summary>
	/// <param name="ctx"></param>
	void RushUpdate(GameContext& ctx);
	/// <summary>
	/// 突進準備中の関数
	/// </summary>
	/// <param name="ctx"></param>
	void PrevRushUpdate(GameContext& ctx);
	
	/// <summary>
	/// ボス出現中の関数
	/// </summary>
	void AppearUpdate() override;
	/// <summary>
	/// アイドル状態の関数
	/// </summary>
	/// <param name="ctx">オブジェクトクラスを継承しているオブジェクトの構造体</param>
	void IdleUpdate(GameContext& ctx) override;

	/// <summary>
	/// 正確には登場前の更新関数
	/// </summary>
	void NoneUpdate() override;
};

