#pragma once

class Input;
class SceneController;	//�V�[���R���g���[���[�̃v���g�^�C�v�錾
/// <summary>
/// �V�[�����N���X
/// </summary>
class Scene
{
protected:
	SceneController& m_controller;

public:
	Scene(SceneController& controller);

	/// <summary>
	/// �V�[���̍X�V����
	/// </summary>
	virtual void Update(Input& input) abstract;

	/// <summary>
	/// �V�[���̕`��
	/// </summary>
	virtual void Draw() abstract;
};