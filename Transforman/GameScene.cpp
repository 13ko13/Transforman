#include "GameScene.h"
#include "Player.h"
#include "Bullet.h"

GameScene::GameScene(SceneController& controller) :
	Scene(controller)
{
	m_pPlayer = std::make_shared<Player>();
	m_bullets.resize(3);
	for (auto& bullet : m_bullets)
	{
		bullet = std::make_shared<Bullet>();
	}
}

void GameScene::Init()
{
	m_pPlayer->Init();
	for (auto& bullet : m_bullets)
	{
		bullet->Init();
	}
}

void GameScene::Update(Input& input)
{
	m_pPlayer->Update(input,m_bullets);
	for (auto& bullet : m_bullets)
	{
		bullet->Update();
	}
}

void GameScene::Draw()
{
	m_pPlayer->Draw();
	for (auto& bullet : m_bullets)
	{
		bullet->Draw();
	}
}
