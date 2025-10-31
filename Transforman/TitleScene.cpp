#include "TitleScene.h"
#include <DxLib.h>
#include "Input.h"
#include "SceneController.h"
#include "Application.h"

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
	if (++m_frame >= fade_interval)
	{
		//�Q�[���V�[���ɐ؂�ւ���
		m_controller.ChangeScene(std::make_shared<Scene>(m_controller));
		//������return����
		return;//�厖
	}
}

void TitleScene::FadeDraw()
{
	//�E�B���h�E�T�C�Y��ϐ��ɕۑ�
	const auto& wsize = Application::GetInstance().GetWindowSize();
	//���S��\��
	DrawRotaGraph(wsize.w / 2, wsize.h / 2, 1.0f, 0.0f, m_titleLogoH, true);
	//�l�͈̔͂���������0.0�`1.0�ɂ��Ă����Ƃ��낢��ƈ����₷���Ȃ�
	auto rate = static_cast<float>(m_frame) / static_cast<float>(fade_interval);
	//a�u�����h
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * rate);//DxLib��Alpha�u�����h��0�`255
	//��ʑS�̂ɍ��t�B������������
	DrawBox(0, 0, wsize.w, wsize.h, 0x000000, true);
	//�u�����h���Ȃ�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::NormalDraw()
{
	//�E�B���h�E�T�C�Y��ϐ��ɕۑ�
	const auto wsize = Application::GetInstance().GetWindowSize();
	//���S��\��
	DrawRotaGraph(wsize.w / 2, wsize.h / 2, 1.0f, 0.0f, m_titleLogoH, true);
}

void TitleScene::Update(Input& input)
{
	//���݊��蓖�Ă��Ă��郁���oUpdate�n�֐������s����
	(this->*m_update)(input);
}

void TitleScene::Draw()
{
	//���蓖�Ă��Ă���Draw�n�����o�֐������s����
	(this->*m_draw)();
}