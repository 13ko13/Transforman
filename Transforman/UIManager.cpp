#include "UIManager.h"
#include "Objects/Player.h"

UIManager::UIManager(std::shared_ptr<Player> pPlayer)
{
	const int playerHP = pPlayer->GetHitPoint();
	playerHpBar = std::make_shared<HpBar>(playerHP);
}

UIManager::~UIManager()
{
}

void UIManager::Update()
{
	//プレイヤーのHPバーの更新
	playerHpBar->Update();
}

void UIManager::Draw()
{
	//プレイヤーのHPバーの描画
	playerHpBar->Draw();
}