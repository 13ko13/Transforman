#pragma once
#include "Scene.h"
#include <memory>
#include <vector>

//プロトタイプ宣言
class Input;
class Player;
class ChargeShotBoss;
class EnemyBullet;
class Camera;
class EnemyBase;
class CollisionManager;
class Object;
class Stage;
class BackGround;
class Map;
class GameScene : public Scene
{
public:
	GameScene(SceneController& controller);
	void Init() override;
	void Update(Input& input) override;
	void Draw()override;

private:
	std::shared_ptr<Player> m_pPlayer;//プレイヤー
	std::vector<std::shared_ptr<PlayerBullet>> m_pPlayerBullets;//プレイヤー弾
	std::vector<std::shared_ptr<EnemyBullet>> m_pEnemyBullets;//敵の弾
	std::vector<std::shared_ptr<EnemyBase>> m_pEnemies;//敵
	std::shared_ptr<ChargeShotBoss> m_pChargeShotBoss;//チャージショットボス
	std::shared_ptr<Camera> m_pCamera;//カメラ
	std::shared_ptr<CollisionManager> m_pColManager;//当たり判定のマネージャー
	std::vector<std::shared_ptr<Object>> m_pObjects;//オブジェクトの配列
	std::shared_ptr<Stage> m_pStage;//ステージデータ
	std::shared_ptr<BackGround> m_pBackground;//背景
	std::shared_ptr<Map> m_pMap;//マップチップ
};

