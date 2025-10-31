#pragma once
#include "Scene.h"
#include <memory>

//プロトタイプ宣言
class Input;
class Player;
class GameScene : public Scene
{
public:
	GameScene(SceneController& controller);
	void Update(Input&)override;
	void Draw()override;

private:
	std::shared_ptr<Player> m_pPlayer;
};

