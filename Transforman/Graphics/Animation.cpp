#include "Animation.h"
#include "Dxlib.h"

Animation::Animation() :
	m_isRepeat(true),
	m_drawHandle(-1),
	m_animIndex(0),
	m_frameSize({ 0.0f,0.0f }),
	m_maxAnimNum(0),
	m_nowAnimNum(0),
	m_oneAnimFrame(0),
	m_frameCount(0),
	m_scale(1.0f),
	m_rotate(0.0f),
	m_drawOffset({0.0f,0.0f})
{
}

Animation::~Animation()
{
}

void Animation::Init(int drawHandle, int animIndex, Vector2 frameSize, int maxAnimNum, int oneAnimFrame, float scale, bool isRepeat)
{
	m_isRepeat = isRepeat;
	m_drawHandle = drawHandle;
	m_animIndex = animIndex;
	m_frameSize = frameSize;
	m_maxAnimNum = maxAnimNum;
	m_oneAnimFrame = oneAnimFrame;
	m_scale = scale;
	m_nowAnimNum = 0;
	m_frameCount = 0;
}

void Animation::Init(int drawHandle, int animIndexY, int animIndexX, Vector2 frameSize, float scale, bool isRepeat)
{
	m_isRepeat = isRepeat;
	m_drawHandle = drawHandle;
	m_animIndex = animIndexY;
	m_frameSize = frameSize;
	m_maxAnimNum = animIndexX + 1;
	m_oneAnimFrame = 0;
	m_scale = scale;
	m_nowAnimNum = animIndexX;
	m_frameCount = 0;
}

void Animation::Update()
{
	if (m_oneAnimFrame == 0) return;	// 1コマあたりのフレーム数が0なら処理を抜ける

	m_frameCount++;	// フレームカウントを進める

	if (m_frameCount >= m_oneAnimFrame)	// 1コマ分のフレームが経過したら
	{
		m_frameCount = 0;
		m_nowAnimNum++;	// アニメーション番号を進める
		if (m_nowAnimNum >= m_maxAnimNum)
		{	// 最大コマ数を超えたら最初に戻す
			if (m_isRepeat)
			{	// 繰り返し再生するなら最初のコマに戻す
				m_nowAnimNum = 0;
			}
		}
	}
}

void Animation::Draw(Vector2 pos, bool isTurn)
{
	// 現在のコマ数が最大コマ数なら描画しない
	if (m_nowAnimNum != m_maxAnimNum)
	{
		DrawRectRotaGraph(pos.x + m_drawOffset.x, pos.y + m_drawOffset.y,
			m_frameSize.x * m_nowAnimNum, m_animIndex * m_frameSize.y,
			m_frameSize.x, m_frameSize.y,
			m_scale, m_rotate, m_drawHandle, true, isTurn);
	}
}

void Animation::Draw(int drawHandle, Vector2 pos, bool isTurn)
{
	if (m_nowAnimNum != m_maxAnimNum)
	{
		DrawRectRotaGraph(pos.x, pos.y,
			m_frameSize.x * m_nowAnimNum, m_animIndex * m_frameSize.y,
			m_frameSize.x, m_frameSize.y,
			m_scale, m_rotate, drawHandle, true, isTurn);
	}
}

bool Animation::GetIsEnd()
{
	if (m_isRepeat) return false;	// 繰り返し再生するなら終了しない

	int totalFrames = m_oneAnimFrame * m_maxAnimNum;	// アニメーション全体のフレーム数
	int currentFrame = m_nowAnimNum * m_oneAnimFrame + m_frameCount;	// 現在のフレーム数
	if (currentFrame >= totalFrames) return true;

	return false;
}

bool Animation::operator!=(const Animation& other) const
{
	if (m_drawHandle != other.m_drawHandle) return true;
	if (m_animIndex != other.m_animIndex) return true;
	if (m_rotate != other.m_rotate) return true;
	if (m_oneAnimFrame != other.m_oneAnimFrame) return true;
	return false;
}
