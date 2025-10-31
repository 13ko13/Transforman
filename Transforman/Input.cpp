#include "Input.h"
#include "DxLib.h"
#include "Fade.h"

Input::Input() :
	m_inputData{},
	m_lastInputData{},
	m_inputTable{}
{
	//イベント名を添え時にして、右辺値に実際の入力種別と押されたボタンの配列を置く
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
	//あらかじめ入力データのための枠を開けておく
	//ここで枠を開けておかないと、チェックの際にAt関数でクラッシュする可能性がある(Null)
	for (const auto& inputInfo : m_inputTable)//forのinputInfoが変更されないようにconstにする
	{
		m_inputData[inputInfo.first] = false;
		m_lastInputData[inputInfo.first] = false;
	}
}

void Input::Update()
{
	//まず入力情報を取得
	char keyState[256];
	GetHitKeyStateAll(keyState);//生のキーボード情報
	int padState = GetJoypadInputState(DX_INPUT_PAD1);//生のPAD1情報
	m_lastInputData = m_inputData;//直前の入力を保存する(前のフレーム情報をコピー)
	//すべての入力イベントをチェックします
	//ここでinputDataが更新される
	//inputTableを回して各イベントの入力をチェックする
	for (const auto& inputInfo : m_inputTable)
	{
		auto& input = m_inputData[inputInfo.first];//inputInfo.firstには"ok"等が入っている
		//inputを書き換えると、inputDataのそのイベントが押されてるか同課を
		//書き換えることになる
		for (const auto& state : inputInfo.second)//InputStateのベクタを回す
		{
			//このループはInputState配列のループなので
			//まず、入力種別をチェックする
			switch (state.type)
			{
			case PeripheralType::keyboard://キーボードの場合
				//GetHitKeyStateAllでとってきた配列の中身を見て
				//入力されているかどうかをチェック
				input = keyState[state.id];
				break;
			case PeripheralType::pad1:
				//GetJoypadInputStateでとってきたビット情報を見て
				//登録されているビット情報と&を取り、そのビットが立っているかどうかを見る
				input = (padState & state.id);
				break;
			}
			if (input)	//大事
			{
				//breakしないとpad1がそのまま残ってしまう
				//最後のチェックで押されてないとfalseになってしまう
				break;
			}
		}
	}
}

bool Input::IsPressed(const char* name)const
{
	//もし「ない」イベントを送られるとクラッシュします
	//もしクラッシュがいやだったら
	//if(inputData.contains(name))
	//{
	//	 return false;//で回避できます。
	//}
	return m_inputData.at(name);//const関数内部なので[]ではなくatを使用してる
}

bool Input::IsTriggerd(const char* name)const
{
	// 今入力されているボタンと
	// 前のフレームで入力されているボタンを比較する
	return m_inputData.at(name) && !m_lastInputData.at(name);
}




