#include "ACV1TextEditor.h"
using namespace std;

bool DumpText(wstring& strFileNmae, unsigned int uCodePage, bool isDoubleLine)
{
	unsigned int lineCount = 1;

	wofstream transFile(strFileNmae + L".txt");
	ifstream scriptFile(strFileNmae);
	transFile.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	if (transFile.is_open() && scriptFile.is_open())
	{
		for (std::string mLine; getline(scriptFile, mLine); lineCount++)
		{
			if (mLine.size() <= 0)
			{
				continue;
			}

			if ((unsigned char)mLine[0] >= 0x7B)
			{
				wstring wLine = StrToWStr(mLine, uCodePage);
				transFile << L"Count:" << setw(0x8) << setfill(L'0') << lineCount << endl;
				transFile << L"Raw:" << wLine << endl;
				if (isDoubleLine)
				{
					transFile << L"Tra:" << wLine << endl << endl;
				}
				else
				{
					transFile << L"Tra:" << endl << endl;
				}
			}
		}
		scriptFile.close();
		transFile.close();
		return true;
	}
	else
	{
		return false;
	}
}

bool InsetText(wstring& strFileName, unsigned int uCodePage)
{
	unsigned int position = 0;
	vector<string> scriptFileLineList;
	vector<wstring> transFileLineList;
	vector<unsigned int> transTextPositionList;

	//Get Trans Text
	wifstream transFile(strFileName + L".txt");
	transFile.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>));
	if (transFile.is_open())
	{
		for (std::wstring wLine; getline(transFile, wLine);)
		{
			if (wLine.find(L"Count:") != string::npos)
			{
				swscanf_s(wLine.c_str(), L"Count:%d", &position);
				getline(transFile, wLine);
				getline(transFile, wLine);
				wLine = wLine.substr(0x4);
				if (!wLine.empty())
				{
					transTextPositionList.push_back(position);
					transFileLineList.push_back(wLine);
				}
			}
		}
		transFile.close();
	}
	else
	{
		return false;
	}


	//Read Script By PerLine
	ifstream scriptFile(strFileName);
	if (scriptFile.is_open())
	{
		for (std::string line; getline(scriptFile, line);)
		{
			scriptFileLineList.push_back(line);
		}
		scriptFile.close();
	}
	else
	{
		return false;
	}


	//Out Script As New File
	ofstream newScriptFile(strFileName + L".new", ios::binary);
	if (newScriptFile.is_open())
	{
		//Replace Trans Text
		for (size_t i = 0; i < transTextPositionList.size(); i++)
		{
			scriptFileLineList[transTextPositionList[i] - 1] = WStrToStr(transFileLineList[i], uCodePage);
		}
		//Write Back All Line
		for (auto& line : scriptFileLineList)
		{
			newScriptFile << line << '\n';
		}
		newScriptFile.close();
	}
	else
	{
		return false;
	}

	return true;
}