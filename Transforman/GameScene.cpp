#include "GameScene.h"
#include "Player.h"
#include "PlayerBullet.h"
#include "ChargeShotBoss.h"
#include "EnemyBullet.h"
#include "Camera.h"

GameScene::GameScene(SceneController& controller) :
	Scene(controller)
{
	// プレイヤーの生成
	m_pPlayer = std::make_shared<Player>();
	// 弾の生成
	m_pBullets.resize(3);
	for (auto& bullet : m_pBullets)
	{
		bullet = std::make_shared<PlayerBullet>();
	}
	// スクリュードライバーの生成
	m_pChargeShotBoss = std::make_shared<ChargeShotBoss>();
	//カメラの生成
	m_pCamera = std::make_shared<Camera>();
}

void GameScene::Init()
{
	// 各オブジェクトの初期化
	m_pPlayer->Init();
	for (auto& bullet : m_pBullets)
	{
		bullet->Init();
	}
	m_pChargeShotBoss->Init();
	m_pChargeShotBoss->SetPlayerPtr(m_pPlayer);
}

void GameScene::Update(Input& input)
{
	// 各オブジェクトの更新
	m_pPlayer->Update(input,m_pBullets);
	for (auto& bullet : m_pBullets)
	{
		bullet->Update();
	}
	m_pChargeShotBoss->Update();
	m_pCamera->Update(*m_pPlayer);
}

void GameScene::Draw()
{
	// 各オブジェクトの描画
	m_pPlayer->Draw(*m_pCamera);
	for (auto& bullet : m_pBullets)
	{
		bullet->Draw(*m_pCamera);
	}
	m_pChargeShotBoss->Draw(*m_pCamera);
}
