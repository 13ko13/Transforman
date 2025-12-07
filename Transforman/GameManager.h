#pragma once
#include <memory>

//プロトタイプ宣言
class Player;
class Camera;
class Stage;

/// <summary>
/// ゲームの進行を管理するクラス
/// </summary>
class GameManager
{
public:
	GameManager();
	~GameManager();

	void Update(std::shared_ptr<Player>& pPlayer,
				std::shared_ptr<Stage>& pStage);
	void Draw();

private:
	bool m_isArrive;//プレイヤーがボスの場所に到着したかどうか
};

