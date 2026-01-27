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
#include "../Objects/ParryBoss.h"
#include "../UIManager.h"
#include "SceneController.h"
#include "GameoverScene.h"
#include "ClearScene.h"
#include "../Main/Application.h"
#include "../EffectFactory.h"
#include "../../Dxlib_h/EffekseerForDXLib.h"
#include "../SoundManager.h"
#include "TextScene.h"
#include <DxLib.h>

namespace
{
	constexpr int p_bullet_max = 10;//プレイヤー弾の最大数
	constexpr int e_bullet_max = 20;//敵弾の最大数
	constexpr int fade_interval = 90;//フェードにかかるフレーム数
}

GameScene::GameScene(SceneController& controller, StageType stageType) :
	Scene(controller),
	m_isClear(false),
	m_isGameover(false)
{
	//ステージデータのロード
	m_pStage = std::make_shared<Stage>();
	m_pStage->Load(1);
	//マップチップの生成
	m_pMap = std::make_shared<Map>(m_pStage);
	m_pMap->SetStageType(StageType::Stage1);

	//エフェクトファクトリーの生成
	m_pEffectFactory = std::make_shared<EffectFactory>();

	// プレイヤーの生成
	m_pPlayer = std::make_shared<Player>(m_pMap,m_pEffectFactory);
	// プレイヤーの弾の生成
	m_pPlayerBullets.resize(p_bullet_max);
	for (auto& bullet : m_pPlayerBullets)
	{
		bullet = std::make_shared<PlayerBullet>(m_pEffectFactory, m_pMap);
	}
	// 敵の弾の生成
	m_pEnemyBullets.resize(e_bullet_max);
	for (auto& bullet : m_pEnemyBullets)
	{
		bullet = std::make_shared<EnemyBullet>(m_pEffectFactory,m_pMap);
	}
	// 敵の生成
	//チャージショットボス、パリィボス、火炎放射ボス、植物系ボスの4体
	m_pEnemies.resize(0);
	//チャージショットボスを試しに追加する
	m_pChargeShotBoss = std::make_shared<ChargeShotBoss>(m_pMap, m_pEffectFactory);
	m_pEnemies.push_back(m_pChargeShotBoss);
	//ToDo:1ステージ完成したらコメント化を解除する
	m_pParryBoss = std::make_shared<ParryBoss>(m_pMap, m_pEffectFactory);
	//m_pEnemies.push_back(m_pParryBoss);

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

	//当たり判定マネージャーの生成
	m_pColManager = std::make_shared<CollisionManager>();

	//UIマネージャーの生成
	m_pUIManager = std::make_shared<UIManager>(m_pPlayer, m_pChargeShotBoss);

	//updateとdrawをフェードインパターンにに切り替えておく
	m_update = &GameScene::UpdateFadeIn;
	m_draw = &GameScene::DrawFade;

	//フェードにかかるフレーム数を代入
	m_frame = fade_interval;

	Init();

	//BGMを再生
	SoundManager::GetInstance().Play(SoundType::GameBgm, true);
}

GameScene::~GameScene()
{
	SoundManager::GetInstance().StopSound(SoundType::GameBgm);
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
	//現在割り当てられているメンバUpdate系関数を実行する
	(this->*m_update)(input);
}

void GameScene::Draw()
{
	//割り当てられているDraw系メンバ関数を実行する
	(this->*m_draw)();
}

void GameScene::UpdateFadeIn(Input&)
{
	//フレームが0以下になったらUpdateとDrawの関数ポインタに
	//関数を参照させる
	m_frame--;
	if (m_frame <= 0)
	{
		m_update = &GameScene::UpdateNormal;
		m_draw = &GameScene::DrawNormal;
		//絶対return
		return;
	}
}

void GameScene::UpdateNormal(Input& input)
{
	GameContext ctx{ m_pEnemyBullets,m_pPlayerBullets,m_pPlayer,m_pStage,input,m_pCamera };
	// 各オブジェクトの更新
	for (auto& object : m_pObjects)
	{
		object->Update(ctx);
	}

	m_pColManager->CheckCollisions(m_pPlayer, m_pEnemies, m_pPlayerBullets, m_pEnemyBullets, m_pParryBoss->GetSwordHitBox(), m_pCamera);

	// カメラの更新
	m_pCamera->Update(m_pPlayer, m_pStage);

	//マップチップの更新
	m_pMap->Update();

	//ゲームマネージャー更新
	m_pGameManager->Update(m_pPlayer, m_pStage, m_pCamera, m_pChargeShotBoss, m_pParryBoss);

	//UIマネージャー更新
	m_pUIManager->Update(m_pPlayer, m_pChargeShotBoss);

	//エフェクトファクトリー更新
	m_pEffectFactory->Update();

	/*std::vector<TextScene::PageDesc> pages = {
		{"img/game/text/move.png"}
	};
	m_controller.PushScene(std::make_shared<TextScene>(m_controller,pages));*/

	//プレイヤーが死んだらフェードアウトに遷移する
	if (m_pPlayer->GetIsDead())
	{
		m_update = &GameScene::UpdateFadeOut;
		m_draw = &GameScene::DrawFade;
		//フェードアウトの最初　念のため
		m_frame = 0;
		m_isClear = false;//クリアしていない
		m_isGameover = true;//ゲームオーバーになった
		//絶対にreturnする
		return;
	}
	else if (m_pChargeShotBoss->GetIsDead())
	{
		m_update = &GameScene::UpdateFadeOut;
		m_draw = &GameScene::DrawFade;
		m_isClear = true;//クリアしていない
		m_isGameover = false;//ゲームオーバーになった
		//フェードアウトの最初　念のため
		m_frame = 0;
		//絶対にreturnする
		return;
	}

	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer2D();
}

void GameScene::UpdateFadeOut(Input& input)
{
	GameContext ctx{ m_pEnemyBullets,m_pPlayerBullets,m_pPlayer,m_pStage,input,m_pCamera };

	//ゲームオーバー時のみプレイヤーを更新する
	if (!m_isClear && m_isGameover)
	{
		m_pPlayer->Update(ctx);
	}
	//エフェクトファクトリー更新
	m_pEffectFactory->Update();

	//フレームを++してfade_intervalを超えたら
	m_frame++;
	//プレイヤーがゲームをクリアしたなら
	//クリアシーンに遷移する
	//死んだならゲームオーバーシーンに遷移する
	if (!m_isClear && m_isGameover)
	{
		if (m_frame >= fade_interval)
		{
			m_controller.ChangeScene(std::make_shared<GameoverScene>(m_controller));

			//絶対にreturnする
			return;
		}
	}
	else if (m_isClear && !m_isGameover)
	{
		if (m_frame >= fade_interval)
		{
			m_controller.ChangeScene(std::make_shared<ClearScene>(m_controller));

			//絶対にreturnする
			return;
		}
	}
}

void GameScene::DrawFade()
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

	//エフェクトファクトリーの描画
	m_pEffectFactory->Draw(m_pCamera);

	//UIマネージャーの描画
	m_pUIManager->Draw();

	//ウィンドウサイズを変数に保存
	//ウィンドウサイズを変数に保存
	const auto& wsize = Application::GetInstance().GetWindowSize();
	//値の範囲をいったん0.0～1.0にしておくといろいろと扱いやすくなる
	auto rate = static_cast<float>(m_frame) / static_cast<float>(fade_interval);
	//aブレンド
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255 * rate));//DxLibのAlphaブレンドが0～255
	//画面全体に黒フィルムをかける
	DrawBox(0, 0, wsize.w, wsize.h, 0x000000, true);
	//ブレンドしない
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameScene::DrawNormal()
{
	//ウィンドウサイズを変数に保存
	const auto wsize = Application::GetInstance().GetWindowSize();

	//背景の描画
	m_pBackground->Draw();
	//マップチップの描画
	m_pMap->Draw(*m_pCamera);
	// 各オブジェクトの描画
	for (auto& object : m_pObjects)
	{
		object->Draw(m_pCamera);
	}

	//UIマネージャーの描画
	m_pUIManager->Draw();

	//エフェクトファクトリーの描画
	m_pEffectFactory->Draw(m_pCamera);

	//Effekseer描画
	DrawEffekseer2D();
}