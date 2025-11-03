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

void GameScene::Update(Input& input)
{
	m_pPlayer->Update(input);
}

void GameScene::Draw()
{
	m_pPlayer->Draw();
}
