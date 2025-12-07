#include "GameManager.h"
#include "Objects/Player.h"

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::Update(std::shared_ptr<Player>& pPlayer,
					std::shared_ptr<Stage>& pStage)
{
	//プレイヤーがボスの場所に到着したら
	//isArriveをtrueにする
	//pPlayer->GetPos().x
}

void GameManager::Draw()
{

}