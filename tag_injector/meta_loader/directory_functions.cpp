#include"..\stdafx.h"
#include"directory_functions.h"

std::string Wchar_to_string(CHAR* wch)
{
	std::string ret = "";

	while (*wch)
		ret += *wch++;

	return ret;
}
LPCSTR string_to_w_char(std::string str)
{
	CHAR* ret = new CHAR[str.length()];

	int i = 0;
	for (; i < str.length(); i++)
		ret[i] = (CHAR)str[i];
	ret[i] = '\0';

	return ret;
}
void read_directory(const std::string& name, std::vector<std::string>& v)
{
	std::string pattern(name);
	pattern.append("\\*");
	WIN32_FIND_DATAA data;
	HANDLE hFind;
	if ((hFind = FindFirstFileA(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			v.push_back(Wchar_to_string(data.cFileName));
		} while (FindNextFileA(hFind, &data) != 0);
		FindClose(hFind);
	}
}