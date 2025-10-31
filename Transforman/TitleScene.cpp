#include "TitleScene.h"
#include <DxLib.h>
#include "Input.h"

//�t�F�[�h�ɂ�����t���[����
constexpr int fade_interval = 60;

TitleScene::TitleScene(SceneController& controller) :
	Scene(controller)
{
	//�^�C�g�����S�n���h���ɉ摜�̃n���h����n��
	m_titleLogoH = LoadGraph(L"img/title/title_logo.png");

	//update��draw�̊֐��|�C���^��FadeInUpdate��
	//FadeDraw���Q�Ƃ�����
	m_update = &TitleScene::FadeInUpdate;
	m_draw = &TitleScene::FadeDraw;

	//frame��fade�ɂ�����b������
	m_frame = fade_interval;
}

void TitleScene::FadeInUpdate(Input&)
{
	//�t���[����0�ȉ��ɂȂ�����Update��Draw�̊֐��|�C���^��
	//�֐����Q�Ƃ�����
	if (--m_frame <= 0)
	{
		m_update = &TitleScene::NormalUpdate;
		m_draw = &TitleScene::NormalDraw;
		//��΂�return������
		return;
	}
}

void TitleScene::NormalUpdate(Input& input)
{
	//ok�{�^���������ꂽ��
	//�֐���؂�ւ��ăt�F�[�h�A�E�g�ɓ���
	if (input.IsTriggerd("ok"))
	{
		m_update = &TitleScene::FadeOutUpdate;
		m_draw = &TitleScene::FadeDraw;
		//�t�F�[�h�A�E�g�̍ŏ��@�O�̂��߁@
		m_frame = 0;
		//��΂�return����
		return;
	}
}

void TitleScene::FadeOutUpdate(Input&)
{
	//�t���[����++����fade_interval�𒴂�����
	//�Q�[���V�[���ɐ؂�ւ���

	//������return����

}

void TitleScene::FadeDraw()
{
	//�E�B���h�E�T�C�Y��ϐ��ɕۑ�

	//���S��\��

	//�l�͈̔͂���������0.0�`1.0�ɂ��Ă����Ƃ��낢��ƈ����₷���Ȃ�

	//a�u�����h

	//��ʑS�̂ɍ��t�B������������

	//�u�����h���Ȃ�

}

void TitleScene::NormalDraw()
{
	//�E�B���h�E�T�C�Y��ϐ��ɕۑ�

	//���S��\��
}

void TitleScene::Update(Input&)
{
	//���݊��蓖�Ă��Ă��郁���oUpdate�n�֐������s����
}

void TitleScene::Draw()
{
	//���蓖�Ă��Ă���Draw�n�����o�֐������s����
}