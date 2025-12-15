#pragma once
#include "Object.h"
#include "../Charactor.h"
#include "../General/Input.h"
#include <vector>
#include <memory>
#include "../Collider/Rect.h"

enum class PlayerState
{
	None,
	Idle,
	Walk,
	Shot,
	Jump,
	ChargeShot,
	Climb,
	Fire,
	Damage
};

enum class WeaponType
{
	Normal,
	Charge,
	Fire
};

class PlayerBullet;
class Player : public Charactor
{
public:
	Player(std::shared_ptr<Map> pMap);
	~Player();

	void Init() override;
	void Update(GameContext& ctx) override;
	void Draw(std::shared_ptr<Camera> pCamera) override;

	void OnArriveEnemy();

	/// <summary>
	/// CollisionManagerに呼ばせる
	/// NockBack開始時の処理
	/// </summary>
	/// <param name="dir">ノックバックさせる方向</param>
	void OnKnockback(int dir);

	/// <summary>
	/// 現在無敵中かどうかを返す関数
	/// </summary>
	/// <returns>true:無敵中,false:無敵ではない</returns>
	const bool GetIsInvincible() const { return m_isInvincible; };

	/// <summary>
	/// 現在弾をチャージしているかどうか
	/// </summary>
	/// <returns>true:チャージ中,false:チャージしていない</returns>
	const bool GetIsCharging() const { return m_isCharging; }

private:
	//変数一覧
	int m_jumpPower;//可変ジャンプ力
	int m_shotCooltime;///ショットのクールタイム管理用
	int m_flameThrowerCT;//火炎放射器のクールタイム管理用
	int m_flameThrowCount;//火炎放射中の時間計測用
	int m_knockackTimer;//ノックバック中のタイム管理用
	int m_blinkingTimer;//無敵中の点滅中のタイム管理用

	/// <note>ジャンプが可能:true,ジャンプ不可能:false</note>
	bool m_isJumping;///ジャンプしているかどうか
	bool m_isCharging;//チャージショットをしているかどうか
	bool m_isArrive;//ボス部屋に到着したかどうか
	bool m_isInvincible;//ダメージを食らった後の無敵中かどうか

	int m_prevChargeFrame;//チャージショットのためのフレーム数
	int m_animSrcX;		  //現在のアニメーションの横の切り取り位置
	int m_animSrcY;		  //現在のアニメーションの縦の切り取り位置
	int m_animIdx;			//現在のアニメーションのインデックス

	float m_damageAnimFrame;	//現在のダメージアニメーションフレーム数

	int m_knockbackDir;			//ノックバックする方向

	PlayerState m_state;
	WeaponType m_weaponType;

private:
	//関数一覧
	/// <summary>
	/// ジャンプ処理
	/// </summary>
	void Jump(Input& input);

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move(Input& input);

	/// <summary>
	/// ショット処理
	/// </summary>
	void Shot(std::vector<std::shared_ptr<PlayerBullet>>& pBullets);

	/// <summary>
	/// チャージショットの処理
	/// </summary>
	/// <param name="pBullet">プレイヤーの弾丸を格納する共有ポインタのベクター</param>
	void ChargeShot(std::vector<std::shared_ptr<PlayerBullet>>& pBullets);

	/// <summary>
	/// 火炎放射をする処理
	/// </summary>
	/// <param name="pBullet">プレイヤーの弾丸を格納する共有ポインタのベクター</param>
	void FireShot(std::vector<std::shared_ptr<PlayerBullet>>& pBullet);

	/// <summary>
	/// ショットを打つ準備の処理
	/// </summary>
	/// <param name="input">イベント名</param>
	/// <param name="pBullets">プレイヤーの弾丸</param>
	void PrevShot(Input& input, std::vector<std::shared_ptr<PlayerBullet>>& pBullets);

	void Climb();

	/// <summary>
	/// Stateを切り替える
	/// </summary>
	/// <param name="state">ステート名</param>
	void ChangeState(PlayerState state);

	/// <summary>
	/// ダメージを食らった時のノックバックモーション
	/// </summary>
	/// <param name="isHIt">当たっている:true,当たっていない:false</param>
	void Knockback();
};