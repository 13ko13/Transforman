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
	// プレイヤーの弾の生成
	m_pPlayerBullets.resize(3);
	for (auto& bullet : m_pPlayerBullets)
	{
		bullet = std::make_shared<PlayerBullet>();
		bullet->SetEnemy(
			for (auto& enemy : m_pEnemies)
			{

			}
	}
	// 敵の弾の生成
	m_pEnemyBullets.resize(20);
	for (auto& bullet : m_pEnemyBullets)
	{
		bullet = std::make_shared<EnemyBullet>();
	}
	// 敵の生成
	//チャージショットボス、壁のぼりボス、火炎放射ボス、植物系ボスの4体
	//m_pEnemies.resize(0);
	//チャージショットボスを試しに追加する
	m_pChargeShotBoss = std::make_shared<ChargeShotBoss>();
	m_pEnemies.push_back(m_pChargeShotBoss);
	//生成した敵の初期化
	for( auto& enemy : m_pEnemies)
	{
		enemy = std::make_shared<ChargeShotBoss>();
	}

	//カメラの生成
	m_pCamera = std::make_shared<Camera>();
}

void GameScene::Init()
{
	// 各オブジェクトの初期化
	m_pPlayer->Init();
	for (auto& bullet : m_pPlayerBullets)
	{
		bullet->Init();
	}
	for( auto& bullet : m_pEnemyBullets)
	{
		bullet->Init();
		bullet->SetPlayer(m_pPlayer);
	}
	for( auto& enemy : m_pEnemies)
	{
		enemy->Init();
		enemy->SetPlayerPtr(m_pPlayer);
	}
}

void GameScene::Update(Input& input)
{
	// 各オブジェクトの更新
	m_pPlayer->Update(input,m_pPlayerBullets);
	for (auto& bullet : m_pPlayerBullets)
	{
		bullet->Update();
	}
	for( auto& bullet : m_pEnemyBullets)
	{
		bullet->Update();
	}
	for( auto& enemy : m_pEnemies)
	{
		enemy->Update();
	}

	m_pCamera->Update(*m_pPlayer);
}

void GameScene::Draw()
{
	// 各オブジェクトの描画
	m_pPlayer->Draw(*m_pCamera);
	for (auto& bullet : m_pPlayerBullets)
	{
		bullet->Draw(*m_pCamera);
	}
	for( auto& bullet : m_pEnemyBullets)
	{
		bullet->Draw(*m_pCamera);
	} 
	for( auto& enemy : m_pEnemies)
	{
		enemy->Draw(*m_pCamera);
	}
}
