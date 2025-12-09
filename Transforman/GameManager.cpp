#include "GameManager.h"
#include "Objects/Player.h"
#include "General/GameConstants.h"
#include "Graphics/Camera.h"
#include "Objects/ChargeShotBoss.h"
#include "Stages/Stage.h"

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
	std::shared_ptr<ChargeShotBoss> pChargeBoss)
{
	//プレイヤーがボスの場所に到着したら
	//isArriveをtrueにする
	if (pPlayer->GetPos().x > Graphic::screen_width)
	{
		m_isArrive = true;
		pCamera->OnArriveEnemy(pPlayer, pStage);
		pPlayer->OnArriveEnemy();

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
}