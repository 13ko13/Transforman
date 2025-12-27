#pragma once
#include <memory>
#include <vector>

//プロトタイプ宣言
class Player;
class Camera;
class Stage;
class EnemyBase;

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
				std::vector<std::shared_ptr<EnemyBase>> pEnemies);

private:
	bool m_isArrive;//プレイヤーがボスの場所に到着したかどうか
	bool m_isAppear;//ボスが出現しているかどうか
};

