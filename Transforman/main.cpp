#include "DxLib.h"
#include "Application.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	auto& app = Application::GetInstance();
	if (!app.Init())
	{
		return -1;
	}
	app.Run();//�Q�[���X�^�[�g(�Q�[�����[�v�ɓ���)
	app.Terminate();//�Q�[���I������
	return 0;				// �\�t�g�̏I�� 
}