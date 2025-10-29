#include "SceneController.h"
#include "Scene.h"

void SceneController::ChangeScene(std::shared_ptr<Scene> scene)
{
	//�����A���X�g����̏ꍇ�A���ʂɑ����ChangeScene���悤�Ƃ����
	//���Rempty�̔��ɑ΂���Change���悤�Ƃ���̂ŁA�N���b�V�����܂�
	//���̂��߁A�ŏ���empty���ǂ������`�F�b�N���܂�
	if (m_scenes.empty())
	{
		///�ŏ��͗v�f���Ȃ�����
		//����ۂ̏ꍇ�ɂ͎w��̗v�f��push���܂�
		//���Ȃ��Ƃ�1�͐ς܂�Ă����Ԃɂ��܂�
		m_scenes.push_back(scene);
	}
	else
	{
		m_scenes.back() = scene;
	}
}

void SceneController::PushScene(std::shared_ptr<Scene> scene)
{
	//�V�����V�[���𖖔��ɐς݂܂�(������ςށH)
	m_scenes.push_back(scene);
}

void SceneController::PopScene()
{
	//�����̃V�[�����폜����
	m_scenes.pop_back();
}

void SceneController::Update(Input& input)
{
	//�����̗v�f�ɑ΂���Update����
	m_scenes.back()->Update(input);
}

void SceneController::Draw()
{
	//Update�����~�߂Ă��ׂ�Draw
	//�|�[�Y�����Ƃ��Ƀv���C�w�i�͎c��
	for (auto& scene : m_scenes)
	{
		scene->Draw();
	}
}