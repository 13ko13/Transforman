#pragma once
#include <memory>

//プロトタイプ宣言
class Player;
class Camera;
class Stage;
class ChargeShotBoss;

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
				std::shared_ptr<ChargeShotBoss> pChargeBoss);

private:
	bool m_isArrive;//プレイヤーがボスの場所に到着したかどうか
	bool m_isAppear;//ボスが出現しているかどうか
};

