#include "Application.h"

constexpr int screen_width = 1280;
constexpr int screen_height = 720;
constexpr int color_bit = 32;

Application::Application():
	m_windowSize(screen_width, screen_height)
{

}

Application::~Application()
{

}

Application& Application::GetInstance()
{
	//static�Ő錾���Ă����Ԃ�
	static Application instance;
	return instance;
}

bool Application::Init()
{
	return false;
}

void Application::Run()
{
}

void Application::Terminate()
{
}
