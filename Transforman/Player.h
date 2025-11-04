#pragma once
#include "Object.h"
#include "Input.h"

enum class PlayerState
{
	Idle,
	Shot,
	Jumpm,
	BigShot,
	Cutter,
	Bomb
};

class Player : public Object
{
public:
	Player();
	~Player();

	void Init() override;
	void Update() override;
	void Update(Input& input);
	void Draw() override;

	/// <summary>
	/// ジャンプ処理
	/// </summary>
	void Jump(Input& input);

private:
	//int m_handle;	//画像ハンドル
	float m_jumpInputFrame;
	bool m_isJump;///ジャンプしているかどうか
};