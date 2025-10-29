#pragma once
#include<string>
class StringFunctions
{
public:
	/// <summary>
	/// マルチバイト文字列(string)→ワイド文字列(wstring)
	/// </summary>
	/// <param name="str">マルチバイト文字列</param>
	/// <returns>ワイド文字列</returns>
	static std::wstring WStringFromString(const std::string& str);
};

