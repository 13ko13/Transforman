#include "Camera.h"
#include "../Objects/Player.h"
#include "../General/GameConstants.h"
#include <cmath>
#include "../Stages/Stage.h"

namespace
{
	const Vector2 first_pos = { 0.0f,0.0f };
	constexpr int scorp_range = 100;
	constexpr float camera_lerp_t = 0.1f;
}

Vector2 Camera::VLerp(const Vector2& start, const Vector2& end, float t)
{
	Vector2 ret;
	ret.x = std::lerp(start.x, end.x, t);
	ret.y = std::lerp(start.y, end.y, t);
	return ret;
}

float Camera::GetWorldOriginX() const
{
	//画面左上(ワールド) = カメラ中心X - 画面幅/2
	return m_pos.x - static_cast<float>(Graphic::screen_width) * 0.5f;
}

float Camera::GetWorldOriginY() const
{
	//今回は縦スクロールしないが、これからのために作っておく
	return m_pos.y - static_cast<float>(Graphic::screen_height) * 0.5f;
}

Camera::Camera()
{
	m_pos = first_pos;
	m_drawOffset = first_pos;
}

Camera::~Camera()
{

}

void Camera::Update(const Player& player,const std::shared_ptr<Stage>& pStage)
{
	//プレイヤーの位置が、カメラの中央から一定以上
	//離れたらカメラの目標をその範囲内に収める
	Vector2 targetPos = m_pos;
	if (player.GetPos().x > m_pos.x + (scorp_range * 0.5f))
	{
		targetPos.x = player.GetPos().x - (scorp_range * 0.5f);
	}
	else if (player.GetPos().x < m_pos.x - (scorp_range * 0.5f))
	{
		targetPos.x = player.GetPos().x + (scorp_range * 0.5f);
	}


	//プレイヤーの位置とカメラの位置を同じにする
	m_pos = VLerp(m_pos, targetPos, camera_lerp_t);

	//ベクトルや計算を使って、「カメラのポジションを動かす」
	//という感覚を保ちたいので、Draw側に足しているcamera.posをいじる
	m_drawOffset.x = m_pos.x * -1;
	//m_drawOffset.y = m_pos.y * -1;
	//その時画面の中央にプレイヤーが来るようにする
	//(camera.posが画面の中央になるようにする) 
	m_drawOffset.x += Graphic::screen_width / 2;
	//m_drawOffset.y += Graphic::screen_height / 2;
}
