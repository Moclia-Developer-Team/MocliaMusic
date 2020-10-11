#include <iostream>
#include <string>
#include <map>

#include "GeneralMessage.h"

using namespace std;

/*bot版本信息*/
string BotHelp()
{
	const string MocMuse_Ver = "1.0.0-4 Release ";
	const string MocMuse_Info = "MocliaMusic by STASWIT Version"
		+ MocMuse_Ver;
	const string Platform = "for Mirai-Http";
	string CI;
#ifdef _MSC_VER
	CI = " [MSVC " + to_string(_MSC_VER) + " "
		+ __DATE__ + " " + __TIME__ + "]"; //编译信息（complite info）
#endif // _MSC_VER
#ifdef __GNUC__
	CI = " [GNUC " + to_string(__GNUC__) + " "
		+ __DATE__ + " " + __TIME__ + "]"; //编译信息（complite info）
#endif // __GNUC__

	const string MocMuse_FullInfo = MocMuse_Info +
		Platform + CI;
	const string MocHelp = "可用指令：\n网易点歌[歌名]";
	string Reply = MocMuse_FullInfo + "\n" + MocHelp;
	return Reply;
}