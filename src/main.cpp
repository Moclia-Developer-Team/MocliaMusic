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
 */

#if defined(WIN32) || defined(_WIN32)
//#include <windows.h>
#endif


#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <thread>
#include <regex>
#include <fstream>

#include <mirai/mirai.h>

#include "GlobalHeader.h"
#include "JsonProcess.h"
#include "HttpProcess.h"
#include "NeteaseMusicProcess.h"
#include "GeneralMessage.h"
#include "Configure.h"

using namespace std;
using namespace Cyan;
using namespace cpr;
using namespace rapidjson;

string input;
int CommandNum;

// 分离式指令系统
void CommandSys()
{
	map<string, int> CommandType = {
		{"stop",1},
		{"about",2}
	};
	while (true)
	{
		try
		{
			cin >> input;
			CommandNum = CommandType[input];
			switch (CommandNum)
			{
			// 结束运行程序
			case 1:
				cout << "[MocliaMusic] 已结束进程" << endl;
				exit(0);
				break;
			// 控制台帮助
			case 2:
				cout << BotHelp() << endl;
				break;
			default:
				cout << "[MocliaMusic] 指令错误" << endl;
				break;
			}
		}
		catch (const std::exception& ex)
		{
			cout << "[MocliaMusic] " << ex.what() << endl;
		}
		
	}
}

int main()
{
	// 配置文件是否存在检查
	FILE* DBSearch = fopen("./BotConfig.db", "rb");
	if (!DBSearch)
	{
		MocliaMusic::configure();
	}
	string host, auth, ip_addr,port_temp;
	int64_t port, qqNum;

#if defined(WIN32) || defined(_WIN32)
	// 切换代码页，让 CMD 可以显示 UTF-8 字符
	system("chcp 65001 && cls");
	// 获取标准输出屏幕缓冲区句柄
	//HANDLE stdh = GetStdHandle(STD_OUTPUT_HANDLE);
	// 设置标题
	//SetConsoleTitle("MocliaMusic");
#endif
	try
	{
		ip_addr = MocliaMusic::readconfig(3);
		// 正则分离ip地址和端口
		regex extract(("([\\S\\s]*):([0-9]*)"),
			regex_constants::ECMAScript | regex_constants::icase);
		smatch result;
		regex_match(ip_addr, result, extract);
		host = result[1];
		port_temp = result[2];
		port = atoi(port_temp.c_str());
		// 机器人QQ号
		qqNum = atoi(MocliaMusic::readconfig(1).c_str());
		// 注册密钥
		auth = MocliaMusic::readconfig(2);
	}
	catch (const std::exception& ex)
	{
		cout << "[MocliaMusic] " << ex.what() << endl;
	}

	QQ_t qqNum_qq = QQ_t(qqNum);

	MiraiBot bot(host, port);
	while (true)
	{
		try
		{
			bot.Auth(auth, qqNum_qq);
			break;
		}
		catch (const std::exception& ex)
		{
			cout << "[MocliaMusic] " << ex.what() << endl;
		}
		MiraiBot::SleepSeconds(10);
	}
//#if defined(WIN32) || defined(_WIN32)
	cout << R"(
==============================================================================
 	     __  __            _ _         __  __           _
 	    |  \/  |          | (_)       |  \/  |         (_)
 	    | \  / | ___   ___| |_  __ _  | \  / |_   _ ___ _  ___
 	    | |\/| |/ _ \ / __| | |/ _` | | |\/| | | | / __| |/ __|
 	    | |  | | (_) | (__| | | (_| | | |  | | |_| \__ | | (__
 	    |_|  |_|\___/ \___|_|_|\__,_| |_|  |_|\__,_|___|_|\___|
 
 =============================================================================)"
		<< endl;
	//SetConsoleTextAttribute(stdh,FOREGROUND_BLUE);
//#endif
	cout << "[MocliaMusic] MocliaMusic正在运行中……" << endl;

	thread CommandSystem(CommandSys);
	CommandSystem.detach();

	map<GID_t, bool> groups;

	// 群聊消息处理
	bot.On<GroupMessage>(
		[&](GroupMessage gm)
		{
			try
			{
				string plain = gm.MessageChain.GetPlainText();
				string msg = plain;
				if (gm.AtMe())
				{
					msg = plain.substr(1);
				}
				if (msg.find("网易点歌") != string::npos)
				{
					string MusicName = msg.substr(strlen("网易点歌"));
					if (MusicName.empty())
					{
						gm.Reply(MessageChain().Plain(
							"使用方式：网易点歌[曲名]"));
						return;
					}
					else
					{
						string app = NeteaseMusic(MusicName);
						if (app == "Music Not Found")
						{
							gm.Reply(MessageChain().Plain("云村中没有这首歌哟。"));
						}
						else
						{
							gm.Reply(MessageChain().App(app));
							cout << "[MocliaMusic]" << gm.Sender.Group.Name << "点歌：" << MusicName << endl;
						}
						return;
					}
				}

				if (msg == "*MusicHelp")
				{
					string Help = BotHelp();
					gm.Reply(MessageChain().Plain(Help));
				}
			}
			catch (const std::exception& ex)
			{
				cout << "[MocliaMusic] " << ex.what() << endl;
			}
		});
	bot.On<FriendMessage>(
		[&](FriendMessage fm)
		{
			try
			{
				string plain = fm.MessageChain.GetPlainText();
				if (plain.find("网易点歌") != string::npos)
				{
					string MusicName = plain.substr(strlen("网易点歌"));
					if (MusicName.empty())
					{
						fm.Reply(MessageChain().Plain(
							"使用方式：网易点歌[曲名]"));
						return;
					}
					else
					{
						string app = NeteaseMusic(MusicName);
						if (app == "Music Not Found")
						{
							fm.Reply(MessageChain().Plain("云村中没有这首歌哟。"));
						}
						else
						{
							fm.Reply(MessageChain().App(app));
						}
						return;
					}
				}

				if (plain == "*MusicHelp")
				{
					string Help = BotHelp();
					fm.Reply(MessageChain().Plain(Help));
				}
			}
			catch (const std::exception& ex)
			{
				cout << "[MocliaMusic] " << ex.what() << endl;
			}
		});

	bot.On<TempMessage>(
		[&](TempMessage tm)
		{
			try
			{
				string plain = tm.MessageChain.GetPlainText();
				if (plain.find("网易点歌") != string::npos)
				{
					string MusicName = plain.substr(strlen("网易点歌"));
					if (MusicName.empty())
					{
						tm.Reply(MessageChain().Plain(
							"使用方式：网易点歌[曲名]"));
						return;
					}
					else
					{
						string app = NeteaseMusic(MusicName);
						if (app == "Music Not Found")
						{
							tm.Reply(MessageChain().Plain("云村中没有这首歌哟。"));
						}
						else
						{
							tm.Reply(MessageChain().App(app));
						}
						return;
					}
				}

				if (plain == "*MusicHelp")
				{
					string Help = BotHelp();
					tm.Reply(MessageChain().Plain(Help));
				}
			}
			catch (const std::exception& ex)
			{
				cout << "[MocliaMusic] " << ex.what() << endl;
			}
		});

	bot.EventLoop();

	return 0;
}