#pragma once
#include "Object.h"
#include "Input.h"
#include <vector>
#include <memory>

class PlayerBullet;
class Player : public Object
{
public:
	Player();
	~Player();

	void Init() override;
	void Update() override;
	void Update(Input& input,std::vector<std::shared_ptr<PlayerBullet>>& pBullets);
	void Draw() override;

	bool GetIsRight() const { return m_isRight; }

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
	/// ショットを打つ準備の処理
	/// </summary>
	/// <param name="input">イベント名</param>
	/// <param name="pBullets">プレイヤーの弾丸</param>
	void PrevShot(Input& input, std::vector<std::shared_ptr<PlayerBullet>>& pBullets);

	void Climb();

private:
	int m_jumpPower;//可変ジャンプ力
	int m_shotCooltime;///ショットのクールタイム管理用

	/// <note>ジャンプが可能:true,ジャンプ不可能:false</note>
	bool m_isJumping;///ジャンプしているかどうか
	bool m_isGround;//接地しているかどうか
	bool m_isRight;//右を向いているかどうか
	bool m_isCharging;//チャージショットをしているかどうか

	int m_prevChargeFrame;//チャージショットのためのフレーム数
	float m_animFrame;		//現在のアニメーションのフレーム数
	int m_animSrcX;		  //現在のアニメーションの横の切り取り位置
	int m_animSrcY;		  //現在のアニメーションの縦の切り取り位置
	int m_animIdx;			//現在のアニメーションのインデックス

	enum class PlayerState
	{
		None,
		Idle,
		Walk,
		Shot,
		Jump,
		ChargeShot,
		Climb,
		Fire
	};
	PlayerState m_state;
};