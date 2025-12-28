#include "EnemyBase.h"
#include "../Graphics/Camera.h"

EnemyBase::EnemyBase(int width,int height,std::shared_ptr<Map> pMap):
	Charactor(width,height,pMap),
	m_appearTime(0),
	m_isStart(false),
	m_isAppear(false)
{
	m_state = State::None;
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init()
{

}

void EnemyBase::Update(GameContext& ctx)
{
	//ボス全体の行動(理想は一体一体の行動をここで決める)
	switch (m_state)
	{
	case State::None:
		NoneUpdate();
		break;
	case State::Appear:
		AppearUpdate();
		break;
	case State::Idle:
		IdleUpdate(ctx);
		break;
	}

	if (m_state == State::Appear ||
		m_state == State::Idle)
	{
		//アニメーション更新
		//全枚数のアニメーションを終えたら
		//1枚目の画像に戻す
		m_idleAnim.Update();
	}
}

void EnemyBase::Draw(std::shared_ptr<Camera> pCamera)
{
	Vector2 drawPos = m_pos + pCamera->GetDrawOffset();
	//アニメーションの描画
	switch (m_state)
	{
	case State::None:
		//何も描画しない
		break;
	case State::Appear:
		m_idleAnim.Draw(drawPos, !m_isRight);
		break;
	case State::Idle:
		m_idleAnim.Draw(drawPos, !m_isRight);
		break;
	}
}

void EnemyBase::Attack()
{

}