#pragma once
#include <vector>
#include <memory>

class Player;
class EnemyBase;
class PlayerBullet;
class EnemyBullet;
class CollisionManager
{
public:
	/// <summary>
	/// すべての当たり判定をチェックする
	/// </summary>
	/// <param name="pPlayer">プレイヤーのポインタ</param>
	/// <param name="pEnemies">エネミーのポインタ</param>
	/// <param name="pPlayerBullets">プレイヤーの弾のポインタ</param>
	/// <param name="pEnemyBullets">敵の弾のポインタ</param>
	static void CheckCollisions(
		std::shared_ptr<Player> pPlayer,
		std::vector<std::shared_ptr<EnemyBase>>& pEnemies,
		std::vector<std::shared_ptr<PlayerBullet>>& pPlayerBullets,
		std::vector<std::shared_ptr<EnemyBullet>>& pEnemyBullets
	);

private:
	/// <summary>
	/// 敵とプレイヤーの当たり判定をチェックする
	/// </summary>
	/// <param name="pPlayer">プレイヤーのポインタ</param>
	/// <param name="pEnemy">エネミーのポインタ</param>
	/// <returns></returns>
	static bool CheckCollision(const Player& player, const EnemyBase& enemy);

	/// <summary>
	/// プレイヤーの弾と敵の当たり判定をチェックする
	/// </summary>
	/// <param name="pPlayerBullet">プレイヤーの弾の参照</param>
	/// <param name="pEnemy">エネミーの参照</param>
	/// <returns></returns>
	static bool CheckCollision(const PlayerBullet& bullet,const EnemyBase& enemy);

	/// <summary>
	/// プレイヤーと敵の弾の当たり判定をチェックする
	/// </summary>
	/// <param name="pPlayer">プレイヤーの参照</param>
	/// <param name="pEnemyBullet">敵の弾の参照</param>
	/// <returns></returns>
	static bool CheckCollision(const Player& player, const EnemyBullet& bullet);

	/// <summary>
	/// エネミーリストから死亡しているエネミーを削除する
	/// </summary>
	/// <param name="pEnemies"></param>
	static void RemoveDeadEnemies(std::vector<std::shared_ptr<EnemyBase>>& pEnemies);

	/// <summary>
	/// 敵が死亡してるかを取得する関数
	/// </summary>
	/// <param name="pEnemy">敵のポインタ</param>
	/// <returns>死んでいる:true,死んでいない:false</returns>
	static bool IsEnemyDead(const std::shared_ptr<EnemyBase>& pEnemy);
};

