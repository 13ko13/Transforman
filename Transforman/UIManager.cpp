#include "UIManager.h"
#include "Objects/Player.h"
#include "Objects/ChargeShotBoss.h"
#include "PlayerHpBar.h"
#include "EnemyHpBar.h"

UIManager::UIManager(std::shared_ptr<Player> pPlayer, std::shared_ptr<ChargeShotBoss> pChargeBoss)
{
	const int playerHP = pPlayer->GetHitPoint();
	playerHpBar = std::make_shared<PlayerHpBar>(playerHP);

	const int enemyHP = pChargeBoss->GetHitPoint();
	enemyHpBar = std::make_shared<EnemyHpBar>(enemyHP);
}

UIManager::~UIManager()
{
}

void UIManager::Update(std::shared_ptr<Player> pPlayer, std::shared_ptr<ChargeShotBoss> pChargeBoss)
{
	//プレイヤーのHPバーの更新
	playerHpBar->Update(pPlayer);
	//エネミーのHPバーの更新
	enemyHpBar->Update(pChargeBoss->GetHitPoint());
}

void UIManager::Draw()
{
	//プレイヤーのHPバーの描画
	playerHpBar->Draw();
	//エネミーのHPバーの描画
	enemyHpBar->Draw();
}