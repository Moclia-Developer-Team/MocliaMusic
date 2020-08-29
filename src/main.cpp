/*==============================================================================
 *			 __  __            _ _         __  __           _
 *			|  \/  |          | (_)       |  \/  |         (_)
 *			| \  / | ___   ___| |_  __ _  | \  / |_   _ ___ _  ___
 *			| |\/| |/ _ \ / __| | |/ _` | | |\/| | | | / __| |/ __|
 *			| |  | | (_) | (__| | | (_| | | |  | | |_| \__ | | (__
 *			|_|  |_|\___/ \___|_|_|\__,_| |_|  |_|\__,_|___|_|\___|
 *
 *==============================================================================
 *	Moclia Music for Mirai-api-http
 *	Copyright (C) 2020 星翛-STASWIT
 *  for Moclia Project & Moclia-Development-Team
 * -----------------------------------------------------------------------------
 *	This program is free software: you can redistribute it and/or modify it 
 *	under the terms of the GNU Affero General Public License as published by 
 *  the Free Software Foundation, either version 3 of the License, or (at your 
 *  option) any later version.
 *
 *	This program is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.
 *	See the GNU Affero General Public License for more details.
 *
 *	You should have received a copy of the GNU Affero General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * -----------------------------------------------------------------------------
 * todo:
 *	酷狗点歌
 *	QQ点歌
 *	初次控制台配置
 */

#include <iostream>
#include <map>
#include <string>
#include <sstream>

#include <mirai/mirai.h>

#include "GlobalHeader.h"
#include "JsonProcess.h"
#include "HttpProcess.h"
#include "NeteaseMusicProcess.h"

using namespace std;
using namespace Cyan;
using namespace cpr;
using namespace rapidjson;

int main()
{
#if defined(WIN32) || defined(_WIN32)
	// 切换代码页，让 CMD 可以显示 UTF-8 字符
	system("chcp 65001");
#endif


	string host = JsonReaderString(".\\BotConfig.json","/host");
	int port = JsonReaderInt(".\\BotConfig.json","/port");
	string qqNum = JsonReaderString(".\\BotConfig.json", "/qq");
	long qqLong = stol(qqNum);
	QQ_t qq = static_cast<QQ_t>(qqLong);
	string auth = JsonReaderString(".\\BotConfig.json", "/authKey");

	MiraiBot bot(host, port);
	while (true)
	{
		try
		{
			bot.Auth(auth, qq);
			break;
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
		}
		MiraiBot::SleepSeconds(10);
	}
	cout << "MocliaMusic正在运行中……" << endl;

	map<GID_t, bool> groups;

	bot.On<Message>(
		[&](Message m)
		{
			try
			{
				string plain = m.MessageChain.GetPlainText();
				if (plain.find("网易点歌") != string::npos)
				{
					string MusicName = plain.substr(12);
					string app = NeteaseMusic(MusicName);
					m.Reply(MessageChain().App(app));
					return;
				}

				if (plain == "/MusicHelp")
				{
					const string MocMuse_Ver = "1.0.0Release";
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
					string MocHelp = "可用指令：\n网易点歌[歌名]";
					string Reply = MocMuse_FullInfo + "\n" + MocHelp;
					m.Reply(MessageChain().Plain(Reply));
				}
			}
			catch (const std::exception& ex)
			{
				cout << ex.what() << endl;
			}
		});

	bot.EventLoop();

	return 0;
}