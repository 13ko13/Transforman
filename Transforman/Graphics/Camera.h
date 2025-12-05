#pragma once
#include "../Utility/Geometry.h"
#include <memory>

class Player;
class Stage;
class Camera
{
public:
	Camera();
	~Camera();

	void Update(const Player& player,const std::shared_ptr<Stage>& pStage);

	const Vector2& GetDrawOffset() const { return m_drawOffset; };
	Vector2 VLerp(const Vector2& start, const Vector2& end, float t);

private:
	Vector2 m_pos;	//実際のカメラのポジション
	Vector2 m_drawOffset;	//全てのDrawObjectに足す値
	int disPlayerToStageSideX;//画面の真ん中からステージの端までの横の距離
};

