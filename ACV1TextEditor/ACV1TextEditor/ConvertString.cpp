#include "ConvertString.h"

std::string WStrToStr(std::wstring& wstrString, UINT uCodePage)
{
	int lenStr = 0;
	std::string result;

	lenStr = WideCharToMultiByte(uCodePage, NULL, wstrString.c_str(), wstrString.size(), NULL, NULL, NULL, NULL);
	char* buffer = new char[lenStr + 1];
	WideCharToMultiByte(uCodePage, NULL, wstrString.c_str(), wstrString.size(), buffer, lenStr, NULL, NULL);
	buffer[lenStr] = '\0';

	result.append(buffer);
	delete[] buffer;
	return result;
}

std::wstring StrToWStr(std::string& strString, UINT uCodePage)
{
	int lenWStr = 0;
	std::wstring result;

	lenWStr = MultiByteToWideChar(uCodePage, NULL, strString.c_str(), strString.size(), NULL, NULL);
	wchar_t* buffer = new wchar_t[lenWStr + 1];
	MultiByteToWideChar(uCodePage, NULL, strString.c_str(), strString.size(), buffer, lenWStr);
	buffer[lenWStr] = '\0';

	result.append(buffer);
	delete[] buffer;
	return result;
}