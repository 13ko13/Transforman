#include "GameManager.h"
#include "Objects/Player.h"
#include "General/GameConstants.h"
#include "Graphics/Camera.h"
#include "Objects/ChargeShotBoss.h"
#include "Stages/Stage.h"
#include "Objects/EnemyBase.h"

namespace
{
	int mapchip_size = 32;//マップチップのサイズ
}

GameManager::GameManager() :
	m_isArrive(false),
	m_isAppear(false)
{
}

GameManager::~GameManager()
{
}

void GameManager::Update(std::shared_ptr<Player> pPlayer,
	std::shared_ptr<Stage> pStage,
	std::shared_ptr<Camera> pCamera,
	std::vector<std::shared_ptr<EnemyBase>> pEnemies)
{
	//プレイヤーがボスの場所に到着したら
	//isArriveをtrueにする
	if (pPlayer->GetPos().x > Graphic::screen_width)
	{
		m_isArrive = true;
		pCamera->OnArriveEnemy(pPlayer, pStage);

		//到着して、ボスが出現中の間はプレイヤーは行動不能にする
		bool isStart = false;

		//現在のステージのボスを取得する
		for(const auto& enemy : pEnemies)
		{
			//現在生きている挑戦中のボスを探す(絶対に1体)
			if(!enemy->GetIsDead())
			{
				//そのボス戦が始まっているかどうかを取得
				isStart = enemy->GetIsStart();
				break;
			}
		}

		
		if (isStart)
		{
			pPlayer->OnStart();
		}
		else
		{
			//ボスの状態が降臨中は行動不能にする
			//現在のステージのボスを取得する
			for(const auto& enemy : pEnemies)
			{
				//現在生きている挑戦中のボスを探す(絶対に1体)
				if(!enemy->GetIsDead())
				{
					if (pChargeBoss->GetState() == 1)
					{
						pPlayer->OnArriveEnemy();
					}
					break;
				}
			}
		}


		//ボスの出現演出を行う(一度だけ)
		//画面の半分
		const int screenHalfW = Graphic::screen_width * 0.5f;//640
		//ステージの横幅から画面の横半分を引いたもの
		const int cameraEndPosX = pStage->GetMapSize().w * mapchip_size - screenHalfW - 1;
		//カメラのポジションがステージ端に来たら
		const bool isCameraArrive = pCamera->GetPos().x >= cameraEndPosX;
		if (!m_isAppear && isCameraArrive)
		{
			pChargeBoss->OnArrive();
			m_isAppear = true;
		}
	}

	//プレイヤーが各ステージのボスを倒したら
	//次のステージへ進むことを許可するのと、
	//倒したボスの能力を開放する
	if()
}