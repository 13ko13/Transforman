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
class GameScene : public Scene
{
public:
	GameScene(SceneController& controller);
	void Init() override;
	void Update(Input& input) override;
	void Draw()override;

private:
	std::shared_ptr<Player> m_pPlayer;
	std::vector<std::shared_ptr<PlayerBullet>> m_pPlayerBullets;
	std::vector<std::shared_ptr<EnemyBullet>> m_pEnemyBullets;
	std::vector<std::shared_ptr<EnemyBase>> m_pEnemies;
	std::shared_ptr<ChargeShotBoss> m_pChargeShotBoss;
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<CollisionManager> m_pColManager;
	std::vector<std::shared_ptr<Object>> m_pObjects;
};

