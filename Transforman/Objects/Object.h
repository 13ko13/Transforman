#pragma once
#include "../Utility/Geometry.h"
#include <memory>
#include <vector>

class Camera;
class Player;
class EnemyBullet;
class PlayerBullet;
class Input;
/// <summary>
/// 継承しているクラスのUpdateで使用可能な引数の構造体
/// </summary>
struct GameContext
{
	std::vector<std::shared_ptr<EnemyBullet>>& p_enemyBullets;
	std::vector<std::shared_ptr<PlayerBullet>>& p_playerBullets;
	std::shared_ptr<Player> player;
	Input& input;
};

class Object
{
public:
	Object(const Vector2& pos,const Vector2& vel);
	virtual ~Object();

	virtual void Init() abstract;
	virtual void Update(GameContext& ctx) abstract;
	virtual void Draw(std::shared_ptr<Camera> pCamera) abstract;

	/// <summary>
	/// 重力を計算する関数
	/// </summary>
	void Gravity();

	const Vector2& GetPos() const { return m_pos; }

protected:
	int m_handle;	//画像のハンドル
	int m_frame;//現在のフレーム数
	int m_animFrame;		//現在のアニメーションのフレーム数

	Vector2 m_pos;
	Vector2 m_velocity;
};

