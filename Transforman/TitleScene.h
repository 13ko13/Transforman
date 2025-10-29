#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
public:
	TitleScene(SceneController&);
	void Update(Input&) override;
	void Draw() override;

private:
	int m_titleLogoH;//�^�C�g�����S�n���h��
	
	//�����o�ϐ��|�C���^���g�p���ē�����Ԃ�����������
	//update�֐���draw�֐����A���݂�TitleScene�̏�Ԃɍ��킹��
	//�؂�ւ��Ă���
	void FadeInUpdate(Input&);//�t�F�[�h�C��Update
	void NormalUpdate(Input&);//�ʏ���Update
	void FadeOutUpdate(Input&);//�t�F�[�h�A�E�gUpdate

	//�֐��|�C���^�������ď�ԑJ�ڂ��y�ɂ���
	using UpdateFunc_t = void(TitleScene::*)(Input&);
	UpdateFunc_t m_update;///update�����o�֐��|�C���^

	void FadeDraw();//�t�F�[�h�C��Draw
	void NormalDraw();//�ʏ���Draw

	//�֐��|�C���^�������ď�ԑJ�ڂ��y�ɂ���
	using DrawFunc_t = void(TitleScene::*)();
	DrawFunc_t m_draw;//draw�����o�֐��|�C���^
};

