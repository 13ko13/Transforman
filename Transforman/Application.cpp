#include "Application.h"
#include "DxLib.h"
#include "Input.h"
#include "SceneController.h"

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
	SetDrawScreen(DX_SCREEN_BACK);
	Input input;//���͂̂��߂̃I�u�W�F�N�g
	SceneController controller;//�V�[�����Ǘ�����I�u�W�F�N�g
	while (ProcessMessage() != -1)
	{
		ClearDrawScreen();
		input.Update();//���͏�Ԃ̍X�V

		//�V�[���̍X�V
		controller.Update(input);
		//�V�[���̕`��
		controller.Draw();
		ScreenFlip();
		//ESC�L�[�������ꂽ��E�B���h�E�����
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
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
