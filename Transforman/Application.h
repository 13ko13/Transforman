#pragma once

/// <summary>
/// �A�v���P�[�V�����S�̂��Ǘ�����
/// �V���O���g���N���X
/// </summary>
class Application
{ 
private:
	Size m_windowSize;

	Application();//new���ϐ��錾���ł��Ȃ��Ȃ�
	Application(const Application& app) = delete;//�R�s�[�R���X�g���N�^�𖳌�
	void operator=(const Application& app) = delete;//������֎~

public:
	~Application();
	
	/// <summary>
	/// Application�̃V���O���g���C���X�^���X���擾����
	/// </summary>
	/// <returns>Application�̃C���X�^���X</returns>
	/// <note>Application�̎��̂͂��̊֐������Ő�������A�����ƂƂǂ܂葱����</note>
	static Application& GetInstance();

	/// <summary>
	/// ����������
	/// </summary>
	/// <returns>����������:true / ���������s:false</returns>
	bool Init();

	/// <summary>
	/// �A�v���P�[�V�������X�^�[�g����
	/// �Q�[�����[�v������
	/// </summary>
	void Run();

	/// <summary>
	/// �A�v���P�[�V�����I������
	/// </summary>
	void Terminate();

	const Size& GetWindowSize() const;
};

