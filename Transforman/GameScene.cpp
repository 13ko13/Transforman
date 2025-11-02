#include "GameScene.h"
#include "Player.h"

GameScene::GameScene(SceneController& controller) :
	Scene(controller)
{
	m_pPlayer = std::make_shared<Player>();
}

void GameScene::Init()
{
	m_pPlayer->Init();
}

void GameScene::Update(Input&)
{
	m_pPlayer->Update();
}

void GameScene::Draw()
{
	m_pPlayer->Draw();
}
