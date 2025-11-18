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
class GameScene : public Scene
{
public:
	GameScene(SceneController& controller);
	void Init() override;
	void Update(Input& input) override;
	void Draw()override;

private:
	std::shared_ptr<Player> m_pPlayer;
	std::vector<std::shared_ptr<PlayerBullet>> m_pBullets;
	std::shared_ptr<ChargeShotBoss> m_pChargeShotBoss;
	std::shared_ptr<Camera> m_pCamera;
};

