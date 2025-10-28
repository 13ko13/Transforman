#pragma once
#include <map>
#include <vector>
#include <string>

/// <summary>
/// ���Ӌ@����
/// </summary>
enum class PeripheralType
{
	keyboard,
	pad1
};

/// <summary>
/// ���͑Ή����
/// </summary>
struct InputState
{
	PeripheralType type;//���͂��ꂽ�@��̎��
	int id;//���͏�񂪓���(�L�[�{�[�h�̏ꍇ�̓C���f�b�N�X�A�p�b�h�̏ꍇ�̓r�b�g)
};

/// <summary>
/// ���͂𒊏ۉ����邽�߂̃N���X
/// </summary>
class Input
{
	//map�͑Ή��\�̂悤�Ȃ���
private:
	std::map<std::string, std::vector<InputState>> m_inputTable;///�C�x���g���Ǝ��ۂ̓��͂̑Ή��\
	std::map<std::string, bool>m_inputData;///���ۂɓ��͂��ꂽ���ǂ����̃f�[�^
	std::map<std::string, bool>m_lastInputData;///�O�̃t���[���ɓ��͂��ꂽ���ǂ����̃f�[�^

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Input();

	/// <summary>
	/// ���t���[���Ăяo���āA
	/// ���͏����X�V������
	/// </summary>
	void Update();

	/// <summary>
	/// ����̃{�^����������Ă��邩
	/// </summary>
	/// <param name="name">�C�x���g��(��:OK,BACK�Ȃ�)</param>
	/// <returns>������Ă���:true,������Ă��Ȃ�:false</returns>
	bool IsPressed(const char* name) const;

	/// <summary>
	/// ����̃{�^�������݉����ꂽ��(�����ꂽ�u�Ԃ̂ݔ�������)
	/// </summary>
	/// <param name="name">�C�x���g��</param>
	/// <returns>�������ꂽ�u��:true,������ĂȂ�or�������ςȂ�:false</returns>
	bool IsTriggerd(const char* name) const;
};

