#pragma once
#include <memory>

//プロトタイプ宣言
class Player;
class Camera;
class Stage;
class ChargeShotBoss;
class ParryBoss;
/// <summary>
/// ゲームの進行を管理するクラス
/// </summary>
class GameManager
{
public:
	GameManager();
	~GameManager();

	void Update(std::shared_ptr<Player> pPlayer,
				std::shared_ptr<Stage> pStage,
				std::shared_ptr<Camera> pCamera,
				std::shared_ptr<ChargeShotBoss> pChargeBoss,
				std::shared_ptr< ParryBoss> pParryBoss);

	/// <summary>
	/// ステージタイプを設定する関数
	/// </summary>
	/// <param name="stageType">ステージのタイプ</param>
	void SetStageType(int stageType) { m_stageType = static_cast<StageType>(stageType); }

private:
	bool m_isArrive;//プレイヤーがボスの場所に到着したかどうか
	bool m_isAppear;//ボスが出現しているかどうか

	void ChargeBossUpdate(std::shared_ptr<Player> pPlayer,
		std::shared_ptr<Stage> pStage,
		std::shared_ptr<Camera> pCamera,
		std::shared_ptr<ChargeShotBoss> pChargeBoss);
	void ParryBossUpdate(std::shared_ptr<Player> pPlayer,
		std::shared_ptr<Stage> pStage,
		std::shared_ptr<Camera> pCamera,
		std::shared_ptr<ParryBoss> pParryBoss);

	enum class StageType
	{
		Stage1,
		Stage2,
		Stage3,
		BossStage,

		StageMax,
	};
	StageType m_stageType;
};

