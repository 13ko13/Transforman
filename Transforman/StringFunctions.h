#pragma once
#include<string>
class StringFunctions
{
public:
	/// <summary>
	/// �}���`�o�C�g������(string)�����C�h������(wstring)
	/// </summary>
	/// <param name="str">�}���`�o�C�g������</param>
	/// <returns>���C�h������</returns>
	static std::wstring WStringFromString(const std::string& str);
};

