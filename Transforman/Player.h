#pragma once
#include "Object.h"
#include "Input.h"
#include <vector>
#include <memory>

enum class PlayerState
{
	Idle,
	Shot,
	Jumpm,
	BigShot,
	Cutter,
	Bomb
}; 

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

private:	
	//int m_handle;	//画像ハンドル
	int m_jumpFrame;//ジャンプ中のフレーム数
	int m_shotCooltime;///ショットのクールタイム管理用

	/// <note>ジャンプが可能:true,ジャンプ不可能:false</note>
	bool m_isJumping;///ジャンプしているかどうか
	bool m_isGround;//接地しているかどうか
	bool m_isRight;//右を向いているかどうか
};