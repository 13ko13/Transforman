#pragma once
#include <memory>

class Player;
class Animation
{
public:
	Animation();
	~Animation();

	void Init();
	void Update();
	void Draw();

	/// <summary>
	/// プレイヤーのアニメーションの種類
	/// </summary>
	enum class PlayerAnim : int
	{
		None = -1,
		Idle = 0,
		Walk,
		Shot,
		Jump,
		ChageShot,
		Climb,
		Fire
	};
private:
	PlayerAnim m_currentAnim;//現在のアニメーション
	int m_attachAnimIndex;//アタッチされているアニメーションの番号
	int m_animFrame;//アニメーションのフレーム数
	bool m_isLoopAnim;//アニメーションが終了したかどうか
};

