#include "GameScene.h"
#include "../Objects/Player.h"
#include "../Objects/PlayerBullet.h"
#include "../Objects/ChargeShotBoss.h"
#include "../Objects/EnemyBullet.h"
#include "../Graphics/Camera.h"
#include "../Collider/CollisionManager.h"
#include "../BackGround.h"
#include "../Stages/Stage.h"
#include "../Map.h"
#include "../GameManager.h"

GameScene::GameScene(SceneController& controller) :
	Scene(controller)
{
	//ステージデータのロード
	m_pStage = std::make_shared<Stage>();
	m_pStage->Load(1);
	//マップチップの生成
	m_pMap = std::make_shared<Map>(m_pStage);
	// プレイヤーの生成
	m_pPlayer = std::make_shared<Player>(m_pMap);
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
	m_pChargeShotBoss = std::make_shared<ChargeShotBoss>(m_pMap);
	m_pEnemies.push_back(m_pChargeShotBoss);

	//キャラクターすべてを配列に入れる
	for (auto& enemy : m_pEnemies)
	{
		m_pCharactors.push_back(enemy);
	}
	m_pCharactors.push_back(m_pPlayer);

	//オブジェクトを継承しているクラスをすべてObjects配列に入れる
	for (auto& charactor : m_pCharactors)
	{
		m_pObjects.push_back(charactor);
	}
	for (auto& bullet : m_pEnemyBullets)
	{
		m_pObjects.push_back(bullet);
	}
	for (auto& bullet : m_pPlayerBullets)
	{
		m_pObjects.push_back(bullet);
	}

	//カメラの生成
	m_pCamera = std::make_shared<Camera>();

	//背景の生成
	m_pBackground = std::make_shared<BackGround>();

	//ゲームマネージャーの生成
	m_pGameManager = std::make_shared<GameManager>();
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
	GameContext ctx{m_pEnemyBullets,m_pPlayerBullets,m_pPlayer,m_pStage,input,m_pCamera};
	// 各オブジェクトの更新
	for (auto& object : m_pObjects)
	{
		object->Update(ctx);
	}
	
	m_pColManager->CheckCollisions(m_pPlayer,m_pEnemies,m_pPlayerBullets,m_pEnemyBullets);

	// カメラの更新
	m_pCamera->Update(m_pPlayer,m_pStage);

	//マップチップの更新
	m_pMap->Update();

	//ゲームマネージャー更新
	m_pGameManager->Update(m_pPlayer,m_pStage,m_pCamera,m_pChargeShotBoss);
}

void GameScene::Draw()
{
	//背景の描画
	m_pBackground->Draw();
	//マップチップの描画
	m_pMap->Draw(*m_pCamera);
	// 各オブジェクトの描画
	for (auto& object : m_pObjects)
	{
		object->Draw(m_pCamera);
	}
}
