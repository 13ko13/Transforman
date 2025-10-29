#pragma once
#include <memory>
#include <list>

//�v���g�^�C�v�錾
class Scene;	
class Input;
class SceneController
{
private:
	//�X�^�b�N�ɐς܂�Ă���V�[�����Ǘ�
	//��ԍŌ�ɐς܂ꂽ�V�[����Update�̂ݎ��s�����
	std::list<std::shared_ptr<Scene>> m_scenes;

public:
	/// <summary>
	/// �V�[���̐؂�ւ�
	/// </summary>
	/// <param name="scene">�V�����V�[��</param>
	void ChangeScene(std::shared_ptr<Scene> scene);

	/// <summary>
	/// �V�[����V�����ς�
	/// </summary>
	/// <param name="scene">�ς݂����V�[��</param>
	void PushScene(std::shared_ptr<Scene> scene);

	/// <summary>
	/// �Ō�ɐς񂾃V�[�������X�g����O��(�����I�ɉ�������)
	/// </summary>
	void PopScene();

	/// <summary>
	/// �����Ɏ����Ă�V�[����Update���Ăяo��
	/// </summary>
	/// <param name="input"></param>
	void Update(Input& input);

	/// <summary>
	/// �����Ɏ����Ă�V�[����Draw���Ăяo��
	/// </summary>
	void Draw();
};