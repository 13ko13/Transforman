#include "CollisionManager.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"
#include "EnemyBase.h"
#include "Player.h"
#include "Geometry.h"
#include <DxLib.h>

void CollisionManager::CheckCollisions(
	std::shared_ptr<Player> pPlayer,
	std::vector<std::shared_ptr<EnemyBase>>& pEnemies,
	std::vector<std::shared_ptr<PlayerBullet>>& pPlayerBullets,
	std::vector<std::shared_ptr<EnemyBullet>>& pEnemyBullets)
{
	//プレイヤーと敵(今のところ使わない)
	for (auto& enemy : pEnemies)
	{
		if (!pPlayer->GetIsDead() &&
			!enemy->GetIsDead() &&
			CheckCollision(*pPlayer, *enemy))
		{
			printfDx("敵と当たった\n");
			//プレイヤーのStateをダメージに変える
			pPlayer->ChangeState(PlayerState::Damage);
			//プレイヤーが右と左どちらから
			//攻撃を受けたかで渡す
			// ノックバックする方向を決める
			int dir = 0;
			bool isRight = false;
			if (pPlayer->GetPos().x > enemy->GetPos().x)//プレイヤーが右にいる場合
			{
				//プレイヤーのノックバックする方向は右
				dir = 1;
				//左向いてからノックバックさせる
				isRight = false;
			}
			else//プレイヤーが左にいる
			{
				//プレイヤーのノックバックする方向は左
				dir = -1;
				//右向いてからノックバックさせる
				isRight = true;
			}
			pPlayer->StartKnockback(dir);
		}
		else
		{
			printfDx("\n");
		}
	}

	//プレイヤーの弾と敵
	for (auto& bullet : pPlayerBullets)
	{
		for (auto& enemy : pEnemies)
		{
			if (bullet->GetIsAlive() &&
				!enemy->GetIsDead() &&
				CheckCollision(*bullet, *enemy))
			{
				//弾の存在を消す
				bullet->SetIsAlive(false);
				//敵の存在を消す(いずれHPをつくるので
				//HPが0になったらというif文も作る
				enemy->SetIsDead(true);
			}
		}
	}

	//プレイヤーと敵の弾
	for (auto& bullet : pEnemyBullets)
	{
		if (!pPlayer->GetIsDead() &&
			bullet->GetIsAlive() &&
			CheckCollision(*pPlayer, *bullet))
		{
			//弾の存在を消す
			bullet->SetIsAlive(false);
			//プレイヤーのStateをダメージに変える
			pPlayer->ChangeState(PlayerState::Damage);
			int dir = 0;
			bool isRight = false;
			if (pPlayer->GetPos().x > bullet->GetPos().x)//プレイヤーが右にいる場合
			{
				//プレイヤーのノックバックする方向は右
				dir = 1.0f;
				//左向いてからノックバックさせる
				isRight = false;
			}
			else//プレイヤーが左にいる
			{
				//プレイヤーのノックバックする方向は左
				dir = -1.0f;
				//右向いてからノックバックさせる
				isRight = true;
			}
			//ノックバックさせる方向と
			//プレイヤーが向く方向を設定
			pPlayer->SetIsRight(isRight);
			pPlayer->StartKnockback(dir);
		}
	}

	RemoveDeadEnemies(pEnemies);
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

bool CollisionManager::IsEnemyDead(const std::shared_ptr<EnemyBase>& pEnemy)
{
	return pEnemy->GetIsDead();
}
