#include "GameScene.h"
#include "Player.h"
#include "PlayerBullet.h"
#include "ChargeShotBoss.h"
#include "EnemyBullet.h"
#include "Camera.h"
#include "CollisionManager.h"

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
	}
	// 敵の弾の生成
	m_pEnemyBullets.resize(20);
	for (auto& bullet : m_pEnemyBullets)
	{
		bullet = std::make_shared<EnemyBullet>();
	}
	// 敵の生成
	//チャージショットボス、壁のぼりボス、火炎放射ボス、植物系ボスの4体
	m_pEnemies.resize(0);
	//チャージショットボスを試しに追加する
	m_pChargeShotBoss = std::make_shared<ChargeShotBoss>();
	m_pEnemies.push_back(m_pChargeShotBoss);

	//オブジェクトを継承しているクラスをすべてObjects配列に入れる
	for (auto& bullet : m_pPlayerBullets)
	{
		m_pObjects.push_back(bullet);
	}
	for (auto& bullet : m_pEnemyBullets)
	{
		m_pObjects.push_back(bullet);
	}
	for (auto& enemy : m_pEnemies)
	{
		m_pObjects.push_back(enemy);
	}
	m_pObjects.push_back(m_pPlayer);//プレイヤーの描画を最優先

	//カメラの生成
	m_pCamera = std::make_shared<Camera>();
}

void GameScene::Init()
{
	// 各オブジェクトの初期化
	for (auto& object : m_pObjects)
	{
		object->Init();
	}
}

void GameScene::Update(Input& input)
{
	GameContext ctx{m_pEnemyBullets,m_pPlayerBullets,m_pPlayer,input};
	// 各オブジェクトの更新
	for (auto& object : m_pObjects)
	{
		object->Update(ctx);
	}
	
	m_pColManager->CheckCollisions(m_pPlayer,m_pEnemies,m_pPlayerBullets,m_pEnemyBullets);

	// カメラの更新
	m_pCamera->Update(*m_pPlayer);
}

void GameScene::Draw()
{
	// 各オブジェクトの描画
	for (auto& object : m_pObjects)
	{
		object->Draw(*m_pCamera);
	}
}
