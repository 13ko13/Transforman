#include "GameManager.h"
#include "Objects/Player.h"
#include "General/GameConstants.h"
#include "Graphics/Camera.h"

GameManager::GameManager():
	m_isArrive(false)
{
}

GameManager::~GameManager()
{
}

void GameManager::Update(std::shared_ptr<Player> pPlayer,
					std::shared_ptr<Stage> pStage,
					std::shared_ptr<Camera> camera)
{
	//プレイヤーがボスの場所に到着したら
	//isArriveをtrueにする
	if (pPlayer->GetPos().x > Graphic::screen_width)
	{
		m_isArrive = true;
		camera->OnArriveEnemy(pPlayer,pStage);
		pPlayer->OnArriveEnemy();
	}
}