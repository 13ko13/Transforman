#include "StringFunctions.h"
#include <DxLib.h>

std::wstring StringFunctions::WStringFromString(const std::string& str)
{
	std::wstring ret;	//戻り値はワイド文字列

	//MultiByteToWideCharの使い方は、２回呼び出す。
	//1回目の呼び出しで、wchar_tのサイズを得る
	//これをしないと、ワイドの方のメモリをどれくらい確保していいかわからないため

	//最初の呼び出しで、ワイド文字列に必要な文字数を返す
	int size = MultiByteToWideChar(CP_ACP,//元のマルチバイト文字列のコードページ
		0,//オプションなし
		str.c_str(),//元の文字列のC言語スタイル文字列
		//最後に\0がついている
		str.length(),//文字列の長さ(保険のため)
		nullptr, 0	//今回は受け取り側がないためnullptr
	);
	//sizeにwchar_tのサイズ(wchar_tがどれくらい必要か)が入っている
	ret.resize(size);//必要なサイズを確保
	//今度は実際に変換を行う
	size = MultiByteToWideChar(CP_ACP,
		0,
		str.c_str(),
		str.length(),
		ret.data(),//受け取り手の先頭アドレス
		ret.size()//受け取り手のサイズ
	);
	return ret;
}