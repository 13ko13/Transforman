#include "GameScene.h"
#include "Player.h"
#include "PlayerBullet.h"
#include "ScrewDriver.h"

GameScene::GameScene(SceneController& controller) :
	Scene(controller)
{
	// プレイヤーの生成
	m_pPlayer = std::make_shared<Player>();
	// 弾の生成
	m_bullets.resize(3);
	for (auto& bullet : m_bullets)
	{
		bullet = std::make_shared<PlayerBullet>();
	}
	// スクリュードライバーの生成
	m_ScrewDrivers.resize(1);
	for (auto& screwDriver : m_ScrewDrivers)
	{
		screwDriver = std::make_shared<ScrewDriver>();
	}
}

void GameScene::Init()
{
	// 各オブジェクトの初期化
	m_pPlayer->Init();
	for (auto& bullet : m_bullets)
	{
		bullet->Init();
	}
	for (auto& screwDriver : m_ScrewDrivers)
	{
		screwDriver->Init();
	}
}

void GameScene::Update(Input& input)
{
	// 各オブジェクトの更新
	m_pPlayer->Update(input,m_bullets);
	for (auto& bullet : m_bullets)
	{
		bullet->Update();
	}
	for (auto& screwDriver : m_ScrewDrivers)
	{
		screwDriver->Update();
	}
}

void GameScene::Draw()
{
	// 各オブジェクトの描画
	m_pPlayer->Draw();
	for (auto& bullet : m_bullets)
	{
		bullet->Draw();
	}
	for (auto& screwDriver : m_ScrewDrivers)
	{
		screwDriver->Draw();
	}
}
