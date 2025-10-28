#include "Input.h"
#include "DxLib.h"

Input::Input() :
	m_inputData{},
	m_lastInputData{},
	m_inputTable{}
{
	//イベント名を添え時にして、右辺値に実際の入力種別と押されたボタンの配列を置く
	m_inputTable["ok"] = { {PeripheralType::keyboard,KEY_INPUT_RETURN},
		{					PeripheralType::pad1,PAD_INPUT_L }};
}
