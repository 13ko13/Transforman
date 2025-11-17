#include "Circle.h"
#include "Rect.h"
#include <cmath>

Circle::Circle()
{
}

Circle::~Circle()
{
}

void Circle::Draw()
{
}

float Circle::GetDistance(Vector2& pos)
{
	float disX = pos.x - m_pos.x;
	float disY = pos.y - m_pos.y;
	return std::sqrt(disX * disX + disY * disY);
}

bool Circle::IsCollWithRect(Rect& rect)
{
	return false;
}

