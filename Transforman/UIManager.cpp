#include "UIManager.h"
#include "Objects/Player.h"

UIManager::UIManager(std::shared_ptr<Player> pPlayer)
{
	const int playerHP = pPlayer->GetHitPoint();
	playerHpBar = std::make_shared<PlayerHpBar>(playerHP);
}

UIManager::~UIManager()
{
}

void UIManager::Update(std::shared_ptr<Player> pPlayer)
{
	//プレイヤーのHPバーの更新
	playerHpBar->Update(pPlayer);
}

void UIManager::Draw()
{
	//プレイヤーのHPバーの描画
	playerHpBar->Draw();
}