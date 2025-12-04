#include "Camera.h"
#include "../Objects/Player.h"
#include "../General/GameConstants.h"
#include <cmath>

namespace
{
	const Vector2 first_pos = { 0.0f,0.0f };
}

Vector2 Camera::VLerp(const Vector2& start, const Vector2& end, float t)
{
	Vector2 ret;
	ret.x = std::lerp(start.x, end.x, t);
	ret.y = std::lerp(start.y, end.y, t);
	return ret;
}

Camera::Camera()
{
	m_pos = first_pos;
	m_drawOffset = first_pos;
}

Camera::~Camera()
{

}

void Camera::Update(const Player& player)
{
	//プレイヤーの位置がステージの端まで来るとカメラの
	//目標ポジションを端より先に行かないようにする


	//プレイヤーの位置とカメラの位置を同じにする
	m_pos = VLerp(m_pos, player.GetPos(), 0.1f);

	//ベクトルや計算を使って、「カメラのポジションを動かす」
	//という感覚を保ちたいので、Draw側に足しているcamera.posをいじる
	m_drawOffset.x = m_pos.x * -1;
	//m_drawOffset.y = m_pos.y * -1;

	//その時画面の中央にプレイヤーが来るようにする
	//(camera.posが画面の中央になるようにする) 
	m_drawOffset.x += Graphic::screen_width / 2;
	//m_drawOffset.y += Graphic::screen_height / 2;
}
