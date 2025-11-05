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

class Shot;
class Player : public Object
{
public:
	Player();
	~Player();

	void Init() override;
	void Update() override;
	void Update(Input& input , std::vector<Bullet>& bulletArray);
	void Draw() override;

	bool GetIsRight() { return m_isRight; }

	/// <summary>
	/// ジャンプ処理
	/// </summary>
	void Jump(Input& input);

private:
	//int m_handle;	//画像ハンドル
	int m_jumpFrame;//ジャンプ中のフレーム数

	/// <note>ジャンプが可能:true,ジャンプ不可能:false</note>
	bool m_isJumping;///ジャンプしているかどうか
	bool m_isGround;//接地しているかどうか
	bool m_isRight;//右を向いているかどうか
};