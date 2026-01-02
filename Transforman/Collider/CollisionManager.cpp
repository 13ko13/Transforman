#include "CollisionManager.h"
#include "../Objects/PlayerBullet.h"
#include "../Objects/EnemyBullet.h"
#include "../Objects/EnemyBase.h"
#include "../Objects/Player.h"
#include "../Utility/Geometry.h"
#include <DxLib.h>
#include "../Collider/Rect.h"
#include "../Objects/ParryBoss.h"

void CollisionManager::CheckCollisions(
	std::shared_ptr<Player>& pPlayer,
	std::vector<std::shared_ptr<EnemyBase>>& pEnemies,
	std::vector<std::shared_ptr<PlayerBullet>>& pPlayerBullets,
	std::vector<std::shared_ptr<EnemyBullet>>& pEnemyBullets,
	const Rect& swordRect)
{
	//プレイヤーと敵(今のところ使わない)
	for (auto& enemy : pEnemies)
	{
		//プレイヤーが生きていて、
		//無敵中ではなくて、
		//敵が生きていて
		//プレイヤーと敵がぶつかっているとき
		if (!pPlayer->GetIsDead() &&
			!pPlayer->GetIsInvincible() &&
			!enemy->GetIsDead() &&
			CheckCollision(*pPlayer, *enemy))
		{
			//プレイヤーが右と左どちらから
			//攻撃を受けたかで渡す
			// ノックバックする方向を決める
			int dir = 0;
			bool isRight = false;
			if (pPlayer->GetColRect().GetCenter().x > enemy->GetColRect().GetCenter().x)//プレイヤーが右にいる場合
			{
				//プレイヤーがすでに左を向いている場合は
				//向きは変えずに、プレイヤーが右を向いているなら
				//向きを敵の方向に向ける
				if (pPlayer->GetIsRight())
				{
					//左向いてからノックバックさせる
					isRight = false;
				}
				//プレイヤーのノックバックする方向は右
				dir = 1;
			}
			else//プレイヤーが左にいる
			{
				//プレイヤーがすでに右を向いている場合は
				//向きは変えずに、プレイヤーが左を向いているなら
				//向きを敵の方向に向ける
				if (pPlayer->GetIsRight())
				{
					//右向いてからノックバックさせる
					isRight = true;
				}
				//プレイヤーのノックバックする方向は左
				dir = -1;
			}
			pPlayer->OnKnockback(dir);
			printfDx("敵とプレイヤーが当たった\n");
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
				enemy->OnDamage();
				//弾の存在を消す
				bullet->SetIsAlive(false);
				//敵の存在を消す(いずれHPをつくるので
				//HPが0になったらというif文も作る
				//enemy->SetIsDead(true);
			}
		}
	}

	//プレイヤーと敵の弾
	for (auto& bullet : pEnemyBullets)
	{
		//プレイヤーが生きていて、
		//無敵中ではなくて、
		//敵弾が生きていて
		//プレイヤーと敵弾がぶつかっているとき
		if (!pPlayer->GetIsDead() &&
			!pPlayer->GetIsInvincible() &&
			bullet->GetIsAlive() &&
			CheckCollision(*pPlayer, *bullet))
		{
			//弾の存在を消す
			bullet->SetIsAlive(false);
			//プレイヤーにノックバックする方向を伝える
			int dir = 0;
			bool isRight = false;
			for (auto& enemy : pEnemies)
			{
				if (pPlayer->GetColRect().GetCenter().x > enemy->GetColRect().GetCenter().x)//プレイヤーが右にいる場合
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
			}
			//ノックバックさせる方向と
			//プレイヤーが向く方向を設定
			pPlayer->SetIsRight(isRight);
			pPlayer->OnKnockback(dir);
		}
	}

	//パリィボスの剣とプレイヤー
	if (CheckCollision(swordRect, *pPlayer))
	{
		//プレイヤーにノックバックする方向を伝える
		int dir = 0;
		bool isRight = false;
		for (auto& enemy : pEnemies)
		{
			if (pPlayer->GetColRect().GetCenter().x > enemy->GetColRect().GetCenter().x)//プレイヤーが右にいる場合
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
		}
		//ノックバックさせる方向と
		//プレイヤーが向く方向を設定
		pPlayer->SetIsRight(isRight);
		pPlayer->OnKnockback(dir);
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

bool CollisionManager::CheckCollision(const Rect& swordRect, const Player& player)
{
	return swordRect.IsCollRect(player.GetColRect());
}

void CollisionManager::RemoveDeadEnemies(std::vector<std::shared_ptr<EnemyBase>>& pEnemies)
{
	pEnemies.erase(std::remove_if(pEnemies.begin(), pEnemies.end(), IsEnemyDead), pEnemies.end());
}

bool CollisionManager::IsEnemyDead(const std::shared_ptr<EnemyBase>& pEnemy)
{
	return pEnemy->GetIsDead();
}
