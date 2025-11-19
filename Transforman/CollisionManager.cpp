#include "CollisionManager.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"
#include "EnemyBase.h"
#include "Player.h"
#include <DxLib.h>

void CollisionManager::CheckCollisions(
	std::shared_ptr<Player> pPlayer,
	std::vector<std::shared_ptr<EnemyBase>>& pEnemies,
	std::vector<std::shared_ptr<PlayerBullet>>& pPlayerBullets,
	std::vector<std::shared_ptr<EnemyBullet>>& pEnemyBullets)
{
	//ÉvÉåÉCÉÑÅ[Ç∆ìG(ç°ÇÃÇ∆Ç±ÇÎégÇÌÇ»Ç¢)
	for (auto& enemy : pEnemies)
	{
		if (!pPlayer->GetIsDead() &&
			!enemy->GetIsDead() &&
			CheckCollision(*pPlayer, *enemy))
		{
			//ñ¢é¿ëïó\íË
		}
	}

	//ÉvÉåÉCÉÑÅ[ÇÃíeÇ∆ìG
	for (auto& bullet : pPlayerBullets)
	{
		for (auto& enemy : pEnemies)
		{
			if (bullet->GetIsAlive() &&
				!enemy->GetIsDead() &&
				CheckCollision(*bullet, *enemy))
			{
				//íeÇÃë∂ç›Çè¡Ç∑
				bullet->SetIsAlive(false);
				//ìGÇÃë∂ç›Çè¡Ç∑(Ç¢Ç∏ÇÍHPÇÇ¬Ç≠ÇÈÇÃÇ≈
				//HPÇ™0Ç…Ç»Ç¡ÇΩÇÁÇ∆Ç¢Ç§ifï∂Ç‡çÏÇÈ
				enemy->SetIsDead(true);
			}
		}
	}

	//ÉvÉåÉCÉÑÅ[Ç∆ìGÇÃíe
	for (auto& bullet : pEnemyBullets)
	{
		if (!pPlayer->GetIsDead() &&
			bullet->GetIsAlive() &&
			CheckCollision(*pPlayer, *bullet))
		{
			//íeÇÃë∂ç›Çè¡Ç∑
			bullet->SetIsAlive(false);
			//ÉvÉåÉCÉÑÅ[ÇÃèàóùÇÕñ¢íË
		}
	}

	RemoveDeadEnemies(pEnemies);
	RemoveDeadEnemyBullets(pEnemyBullets);
	RemoveDeadPlayerBullets(pPlayerBullets);
}


bool CollisionManager::CheckCollision(const Player& player, const EnemyBase& enemy)
{
	return false;
}

bool CollisionManager::CheckCollision(const PlayerBullet& bullet, const EnemyBase& enemy)
{
	return false;
}

bool CollisionManager::CheckCollision(const Player& player, const EnemyBullet& bullet)
{
	return false;
}

void CollisionManager::RemoveDeadEnemies(std::vector<std::shared_ptr<EnemyBase>>& pEnemies)
{

}

void CollisionManager::RemoveDeadEnemyBullets(std::vector<std::shared_ptr<EnemyBullet>>& pEnemyBullets)
{

}

void CollisionManager::RemoveDeadPlayerBullets(std::vector<std::shared_ptr<PlayerBullet>>& pPlayerBullets)
{

}
