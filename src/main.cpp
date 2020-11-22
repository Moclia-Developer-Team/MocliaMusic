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

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <thread>
#include <regex>
#include <ctime>

#include <mirai/mirai.h>
#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/chrono.h>

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
using namespace std::literals::chrono_literals;

string input;
int CommandNum;
time_t MainTime;

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
			MainTime = std::time(nullptr);
			CommandNum = CommandType[input];
			switch (CommandNum)
			{
			// 结束运行程序
			case 1:
				fmt::print(fg(fmt::color::aqua),
					"[MocliaMusic {:%H:%M:%S} &stop] 已结束进程\n",
					*localtime(&MainTime));
				exit(0);
				break;
			// 控制台帮助
			case 2:
				fmt::print(fg(fmt::color::light_sea_green),
					"{}\n",
					BotHelp());
				break;
			// 指令错误回复
			default:
				fmt::print(fg(fmt::color::red), 
					"[MocliaMusic {:%H:%M:%S} &err] 指令错误\n", 
					*localtime(&MainTime));
				break;
			}
		}
		catch (const std::exception& ex)
		{
			MainTime = std::time(nullptr);
			fmt::print(fg(fmt::color::red),
				"[MocliaMusic {:%H:%M:%S} &err] {}\n",
				*localtime(&MainTime), ex.what());
		}
		
	}
}

int main()
{
	MainTime = std::time(nullptr);
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
	// 设置标题
	SetConsoleTitle("MocliaMusic");
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
		MainTime = std::time(nullptr);
		fmt::print(fg(fmt::color::red),
			"[MocliaMusic {:%H:%M:%S} &err] {}\n",
			*localtime(&MainTime), ex.what());
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
			MainTime = std::time(nullptr);
			fmt::print(fg(fmt::color::red),
				"[MocliaMusic {:%H:%M:%S} &err] {}\n",
				*localtime(&MainTime), ex.what());
		}
		MiraiBot::SleepSeconds(10);
	}

	fmt::print(fg(fmt::color::light_sky_blue),
		"{}\n",
		R"(
==============================================================================
 	     __  __            _ _         __  __           _
 	    |  \/  |          | (_)       |  \/  |         (_)
 	    | \  / | ___   ___| |_  __ _  | \  / |_   _ ___ _  ___
 	    | |\/| |/ _ \ / __| | |/ _` | | |\/| | | | / __| |/ __|
 	    | |  | | (_) | (__| | | (_| | | |  | | |_| \__ | | (__
 	    |_|  |_|\___/ \___|_|_|\__,_| |_|  |_|\__,_|___|_|\___|
 
 =============================================================================)"
	);

	fmt::print(fg(fmt::color::aqua),
		"[MocliaMusic {:%H:%M:%S} &startup] MocliaMusic正在运行中……\n",
		*localtime(&MainTime));

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
							gm.Reply(
								MessageChain().Plain("云村中没有这首歌哟。"));
						}
						else
						{
							gm.Reply(MessageChain().App(app));
							MainTime = std::time(nullptr);
							fmt::print(fg(fmt::color::spring_green),
								"[MocliaMusic {:%H:%M:%S} &group] {}({})点歌：{}\n"
								, *localtime(&MainTime),
								gm.Sender.Group.Name, gm.Sender.Group.GID,
								MusicName);
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
				MainTime = std::time(nullptr);
				fmt::print(fg(fmt::color::red),
					"[MocliaMusic {:%H:%M:%S} &err] {}\n",
					*localtime(&MainTime), ex.what());
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
							MainTime = std::time(nullptr);
							fmt::print(fg(fmt::color::chocolate),
								"[MocliaMusic {:%H:%M:%S} &friend] {}({})点歌：{}\n"
								, *localtime(&MainTime),
								fm.Sender.NickName, fm.Sender.QQ,
								MusicName);
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
				MainTime = std::time(nullptr);
				fmt::print(fg(fmt::color::red),
					"[MocliaMusic {:%H:%M:%S} &err] {}\n",
					*localtime(&MainTime), ex.what());
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
							MainTime = std::time(nullptr);
							fmt::print(fg(fmt::color::navajo_white),
								"[MocliaMusic {:%H:%M:%S} &temp] {}({})点歌：{}\n"
								, *localtime(&MainTime),
								tm.Sender.MemberName, tm.Sender.QQ,
								MusicName);
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
				MainTime = std::time(nullptr);
				fmt::print(fg(fmt::color::red),
					"[MocliaMusic {:%H:%M:%S} &err] {}\n",
					*localtime(&MainTime), ex.what());
			}
		});

	bot.EventLoop();

	return 0;
}