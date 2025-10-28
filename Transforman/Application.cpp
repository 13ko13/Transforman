#include "Application.h"
#include "DxLib.h"
#include "Input.h"

constexpr int screen_width = 1280;
constexpr int screen_height = 720;
constexpr int color_bit = 32;

Application::Application():
	m_windowSize{screen_width,screen_height}
{

}

Application::~Application()
{

}

Application& Application::GetInstance()
{
	//staticで宣言してそれを返す
	static Application instance;
	return instance;
}

bool Application::Init()
{
	return false;
}

void Application::Run()
{
	SetDrawScreen(DX_SCREEN_BACK);
	Input input;//入力のためのオブジェクト

	while (ProcessMessage() != -1)
	{
		ClearDrawScreen();
		input.Update();//入力状態の更新

		//シーンの更新

		//シーンの描画

		ScreenFlip();
	}
}

void Application::Terminate()
{
	DxLib_End();
}

const Size& Application::GetWindowSize() const
{
	return m_windowSize;
}
