#include "Application.h"
#include "DxLib.h"
#include "Input.h"
#include "SceneController.h"
#include <memory>
#include "TitleScene.h"
#include "GameConstants.h"

Application::Application():
	m_windowSize{Graphic::screen_width,Graphic::screen_height}
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
	SetGraphMode(m_windowSize.w, m_windowSize.h, Graphic::color_bit);
	//ウィンドwモード設定
	ChangeWindowMode(true);
	//ゲーム名
	SetWindowText(L"TransforMan");
	if (DxLib_Init() == -1)
	{
		return false;
	}
	return true;
}

void Application::Run()
{
	SetDrawScreen(DX_SCREEN_BACK);
	Input input;//入力のためのオブジェクト
	SceneController controller;//シーンを管理するオブジェクト
	controller.ChangeScene(std::make_shared<TitleScene>(controller));
	controller.Init();

	while (ProcessMessage() != -1)
	{
		auto startTime = GetNowHiPerformanceCount();

		ClearDrawScreen();
		input.Update();//入力状態の更新

		//シーンの更新
		controller.Update(input);
		//シーンの描画
		controller.Draw();
		ScreenFlip();
		//ESCキーが押されたらウィンドウを閉じる
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		while (GetNowHiPerformanceCount() - startTime < 16667)
		{

		}
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
