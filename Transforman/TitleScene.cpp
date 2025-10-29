#include "TitleScene.h"
#include <DxLib.h>

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

void TitleScene::Update(Input&)
{
}

void TitleScene::Draw()
{
}

void TitleScene::FadeInUpdate(Input&)
{
}

void TitleScene::NormalUpdate(Input&)
{
}

void TitleScene::FadeOutUpdate(Input&)
{
}

void TitleScene::FadeDraw()
{
}

void TitleScene::NormalDraw()
{
}
