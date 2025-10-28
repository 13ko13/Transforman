#include "Input.h"
#include "DxLib.h"

Input::Input() :
	m_inputData{},
	m_lastInputData{},
	m_inputTable{}
{
	//�C�x���g����Y�����ɂ��āA�E�Ӓl�Ɏ��ۂ̓��͎�ʂƉ����ꂽ�{�^���̔z���u��
	m_inputTable["ok"] = { {PeripheralType::keyboard,KEY_INPUT_RETURN},
		{					PeripheralType::pad1,PAD_INPUT_L }};
}
