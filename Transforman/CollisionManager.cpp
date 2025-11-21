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
	return player.GetColRect().IsCollRect(enemy.GetColRect());
}

bool CollisionManager::CheckCollision(const PlayerBullet& bullet, const EnemyBase& enemy)
{
	return bullet.GetCircle().IsCollWithRect(enemy.GetColRect());
}

bool CollisionManager::CheckCollision(const Player& player, const EnemyBullet& bullet)
{
	return bullet.GetCircle().IsCollWithRect(player.GetColRect());
}

void CollisionManager::RemoveDeadEnemies(std::vector<std::shared_ptr<EnemyBase>>& pEnemies)
{
	pEnemies.erase(std::remove_if(pEnemies.begin(), pEnemies.end(), IsEnemyDead), pEnemies.end());
}

void CollisionManager::RemoveDeadEnemyBullets(std::vector<std::shared_ptr<EnemyBullet>>& pEnemyBullets)
{
	pEnemyBullets.erase(std::remove_if(pEnemyBullets.begin(), pEnemyBullets.end(), IsEnemyBulletDead), pEnemyBullets.end());
}

void CollisionManager::RemoveDeadPlayerBullets(std::vector<std::shared_ptr<PlayerBullet>>& pPlayerBullets)
{
	pPlayerBullets.erase(std::remove_if(pPlayerBullets.begin(), pPlayerBullets.end(), IsPlayerBulletDead), pPlayerBullets.end());
}

bool CollisionManager::IsEnemyDead(const std::shared_ptr<EnemyBase>& pEnemy) const
{
	return pEnemy->GetIsDead();
}

bool CollisionManager::IsEnemyBulletDead(const std::shared_ptr<EnemyBullet>& pBullet) const
{
	return !pBullet->GetIsAlive();
}

bool CollisionManager::IsPlayerBulletDead(const std::shared_ptr<PlayerBullet>& pBullet) const
{
	return !pBullet->GetIsAlive();
}
