#include "StringFunctions.h"
#include <DxLib.h>

std::wstring StringFunctions::WStringFromString(const std::string& str)
{
	std::wstring ret;	//�߂�l�̓��C�h������

	//MultiByteToWideChar�̎g�����́A�Q��Ăяo���B
	//1��ڂ̌Ăяo���ŁAwchar_t�̃T�C�Y�𓾂�
	//��������Ȃ��ƁA���C�h�̕��̃��������ǂꂭ�炢�m�ۂ��Ă������킩��Ȃ�����

	//�ŏ��̌Ăяo���ŁA���C�h������ɕK�v�ȕ�������Ԃ�
	int size = MultiByteToWideChar(CP_ACP,//���̃}���`�o�C�g������̃R�[�h�y�[�W
		0,//�I�v�V�����Ȃ�
		str.c_str(),//���̕������C����X�^�C��������
		//�Ō��\0�����Ă���
		str.length(),//������̒���(�ی��̂���)
		nullptr, 0	//����͎󂯎�葤���Ȃ�����nullptr
	);
	//size��wchar_t�̃T�C�Y(wchar_t���ǂꂭ�炢�K�v��)�������Ă���
	ret.resize(size);//�K�v�ȃT�C�Y���m��
	//���x�͎��ۂɕϊ����s��
	size = MultiByteToWideChar(CP_ACP,
		0,
		str.c_str(),
		str.length(),
		ret.data(),//�󂯎���̐擪�A�h���X
		ret.size()//�󂯎���̃T�C�Y
	);
	return ret;
}