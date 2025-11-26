#pragma once
#include "Object.h"
#include "Input.h"
#include <vector>
#include <memory>
#include "Rect.h"

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
class Player : public Object
{
public:
	Player();
	~Player();

	void Init() override;
	void Update(GameContext& ctx) override;
	void Draw(Camera camera) override;

	const bool GetIsRight() const { return m_isRight; }

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

	/// <summary>
	/// 矩形の参照を返す
	/// </summary>
	/// <returns>参照された矩形</returns>
	const Rect& GetColRect() const { return m_colRect; }

	/// <summary>
	/// プレイヤーが死亡しているかどうかを返す
	/// </summary>
	/// <returns>死んでいる:true,生きている:false</returns>
	const bool GetIsDead() const { return m_isDead; }

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

	/// <summary>
	/// CollisionManagerに呼ばせる
	/// NockBack開始時の処理
	/// </summary>
	/// <param name="dir">ノックバックさせる方向</param>
	void StartKnockback(int dir);

	/// <summary>
	/// 右向きか左向きかを設定する
	/// </summary>
	/// <param name="isRight">true:右向き,false:左向き</param>
	void SetIsRight(bool isRight) { m_isRight = isRight; }

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
	int m_jumpPower;//可変ジャンプ力
	int m_shotCooltime;///ショットのクールタイム管理用
	int m_knockackTimer;//ノックバック中のタイム管理用
	int m_blinkingTimer;//無敵中の点滅中のタイム管理用

	/// <note>ジャンプが可能:true,ジャンプ不可能:false</note>
	bool m_isJumping;///ジャンプしているかどうか
	bool m_isGround;//接地しているかどうか
	bool m_isRight;//右を向いているかどうか
	bool m_isCharging;//チャージショットをしているかどうか
	bool m_isDead;//死亡しているかどうか
	bool m_isInvincible;//ダメージを食らった後の無敵中かどうか

	int m_prevChargeFrame;//チャージショットのためのフレーム数
	float m_animFrame;		//現在のアニメーションのフレーム数
	int m_animSrcX;		  //現在のアニメーションの横の切り取り位置
	int m_animSrcY;		  //現在のアニメーションの縦の切り取り位置
	int m_animIdx;			//現在のアニメーションのインデックス

	float m_damageAnimFrame;	//現在のダメージアニメーションフレーム数

	int m_knockbackDir;			//ノックバックする方向

	PlayerState m_state;
	WeaponType m_weaponType;

	Rect m_colRect;
};