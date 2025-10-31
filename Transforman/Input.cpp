#include "Input.h"
#include "DxLib.h"
#include "Fade.h"

Input::Input() :
	m_inputData{},
	m_lastInputData{},
	m_inputTable{}
{
	//�C�x���g����Y�����ɂ��āA�E�Ӓl�Ɏ��ۂ̓��͎�ʂƉ����ꂽ�{�^���̔z���u��
	m_inputTable["ok"] = { {PeripheralType::keyboard,KEY_INPUT_RETURN},
							{PeripheralType::pad1,PAD_INPUT_L } };
	m_inputTable["shot"] = { {PeripheralType::keyboard,KEY_INPUT_Z},
							{PeripheralType::pad1,PAD_INPUT_X} };
	m_inputTable["up"] = { {PeripheralType::keyboard,KEY_INPUT_UP},
							{PeripheralType::pad1,KEY_INPUT_UP } };
	m_inputTable["down"] = { {PeripheralType::keyboard,KEY_INPUT_DOWN},
							{PeripheralType::pad1,KEY_INPUT_DOWN } };
	m_inputTable["left"] = { {PeripheralType::keyboard,KEY_INPUT_LEFT},
								{PeripheralType::pad1,KEY_INPUT_LEFT } };
	m_inputTable["right"] = { {PeripheralType::keyboard,KEY_INPUT_RIGHT},
							{PeripheralType::pad1,KEY_INPUT_RIGHT } };
	//���炩���ߓ��̓f�[�^�̂��߂̘g���J���Ă���
	//�����Řg���J���Ă����Ȃ��ƁA�`�F�b�N�̍ۂ�At�֐��ŃN���b�V������\��������(Null)
	for (const auto& inputInfo : m_inputTable)//for��inputInfo���ύX����Ȃ��悤��const�ɂ���
	{
		m_inputData[inputInfo.first] = false;
		m_lastInputData[inputInfo.first] = false;
	}
}

void Input::Update()
{
	//�܂����͏����擾
	char keyState[256];
	GetHitKeyStateAll(keyState);//���̃L�[�{�[�h���
	int padState = GetJoypadInputState(DX_INPUT_PAD1);//����PAD1���
	m_lastInputData = m_inputData;//���O�̓��͂�ۑ�����(�O�̃t���[�������R�s�[)
	//���ׂĂ̓��̓C�x���g���`�F�b�N���܂�
	//������inputData���X�V�����
	//inputTable���񂵂Ċe�C�x���g�̓��͂��`�F�b�N����
	for (const auto& inputInfo : m_inputTable)
	{
		auto& input = m_inputData[inputInfo.first];//inputInfo.first�ɂ�"ok"���������Ă���
		//input������������ƁAinputData�̂��̃C�x���g��������Ă邩���ۂ�
		//���������邱�ƂɂȂ�
		for (const auto& state : inputInfo.second)//InputState�̃x�N�^����
		{
			//���̃��[�v��InputState�z��̃��[�v�Ȃ̂�
			//�܂��A���͎�ʂ��`�F�b�N����
			switch (state.type)
			{
			case PeripheralType::keyboard://�L�[�{�[�h�̏ꍇ
				//GetHitKeyStateAll�łƂ��Ă����z��̒��g������
				//���͂���Ă��邩�ǂ������`�F�b�N
				input = keyState[state.id];
				break;
			case PeripheralType::pad1:
				//GetJoypadInputState�łƂ��Ă����r�b�g��������
				//�o�^����Ă���r�b�g����&�����A���̃r�b�g�������Ă��邩�ǂ���������
				input = (padState & state.id);
				break;
			}
			if (input)	//�厖
			{
				//break���Ȃ���pad1�����̂܂܎c���Ă��܂�
				//�Ō�̃`�F�b�N�ŉ�����ĂȂ���false�ɂȂ��Ă��܂�
				break;
			}
		}
	}
}

bool Input::IsPressed(const char* name)const
{
	//�����u�Ȃ��v�C�x���g�𑗂���ƃN���b�V�����܂�
	//�����N���b�V�������₾������
	//if(inputData.contains(name))
	//{
	//	 return false;//�ŉ���ł��܂��B
	//}
	return m_inputData.at(name);//const�֐������Ȃ̂�[]�ł͂Ȃ�at���g�p���Ă�
}

bool Input::IsTriggerd(const char* name)const
{
	// �����͂���Ă���{�^����
	// �O�̃t���[���œ��͂���Ă���{�^�����r����
	return m_inputData.at(name) && !m_lastInputData.at(name);
}




