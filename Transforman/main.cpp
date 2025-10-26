#include "DxLib.h"

namespace
{
	int constexpr kScreenWidth = 1280;
	int constexpr kScreenHeight = 720;
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);

	SetGraphMode(kScreenWidth, kScreenHeight,0);

	SetMainWindowText("Puyo Stack");

	SetWindowSizeChangeEnableFlag(TRUE);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	//�`���𗠉�ʂɐݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	while (ProcessMessage() == 0)
	{
		//���̃t���[���̊J�n���Ԃ��擾
		LONGLONG start = GetNowHiPerformanceCount();

		//��ʂ��N���A
		ClearDrawScreen();

		//ESC�L�[�������ꂽ��E�B���h�E�����
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		//�����ɃQ�[���̏����Ȃǂ�����
		

		//�`��

		//����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();

		//�t���[�����[�g��60�ɌŒ�
		while (GetNowHiPerformanceCount() - start < 16667)
		{

		}

		//ESC�L�[�������ꂽ��E�B���h�E�����
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
	}

	//��������̃O���t�B�b�N���J��


	WaitKey();				// �L�[���͑҂�

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}