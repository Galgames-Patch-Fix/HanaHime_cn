#pragma once
#include <Windows.h>
#include <string>

std::string WStrToStr(std::wstring& wstrString, UINT uCodePage);
std::wstring StrToWStr(std::string& strString, UINT uCodePage);
