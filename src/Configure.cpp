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
 * 功能：配置文件处理
 * todo：配置文件验证
 */

#include <memory>
#include <iostream>
#include <string>
#include <map>
#include <regex>
#include <ctime>

#include <SQLiteCpp/SQLiteCpp.h>
#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/chrono.h>

#include <Configure.h>

using namespace std;
using namespace SQLite;
using namespace std::literals::chrono_literals;

time_t ConTime;

namespace MocliaMusic
{
	std::unique_ptr<SQLite::Database> db;

	void configure()
	{
		try
		{
			// 创建必要变量
			int qq = 10000;
			string host = "127.0.0.1:8080", auth = "12345678", confirm = "y";

			// 初期配置
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
				"欢迎使用MocliaMusic，请根据引导进行初始化配置。\n");
			cout << "请输入您的机器人QQ账号：";
			cin >> qq;
			cout << "请输入您的MiraiAPIHttp地址，例如(127.0.0.1:8080)：";
			cin >> host;
			cout << "请输入您的MiraiAPIHTTP AuthKey：";
			cin >> auth;
			cout << "请确认您的链接信息：" << endl
				<< "机器人账号："
				<< qq << endl
				<< "连接地址："
				<< host << endl
				<< "AuthKey："
				<< auth << endl
				<< "确认写入？(y/n)：";
			cin >> confirm;



			if (confirm == "y")
			{
				// 链接数据库
				db = nullptr;
				db = std::make_unique<SQLite::Database>("./BotConfig.db", OPEN_CREATE | OPEN_READWRITE);
				Transaction Tran(*db);
				// 创建数据表
				db->exec("CREATE TABLE IF NOT EXISTS Program (number INTEAGER, bot_id INTEAGER, auth TEXT, ip_addr TEXT)");
				db->exec("CREATE TABLE IF NOT EXISTS Groups (group_id INTEAGER, bot_on BOOLEAN, default_service TEXT)");
				// 写入数据
				Statement st(*db, "INSERT INTO Program (number, bot_id, auth, ip_addr) VALUES (1, ?, ?, ?)");
				st.bind(1, qq);
				st.bind(2, auth);
				st.bind(3, host);
				st.exec();
				// 确认更改
				Tran.commit();
			}
			else
			{
				// 退出
				exit(0);
			}
		}
		catch (const std::exception& ex)
		{
			ConTime = std::time(nullptr);
			fmt::print(fg(fmt::color::red),
				"[MocliaMusic {:%H:%M:%S} &err] {}\n",
				*localtime(&ConTime), ex.what());
		}

	}

	string readconfig(int num)
	{
		try
		{
			// 连接数据库
			db = nullptr;
			db = std::make_unique<SQLite::Database>("./BotConfig.db");
			// 查找内容
			Statement ReadSt(*db, "SELECT * FROM Program WHERE number = 1");
			if (ReadSt.executeStep())
			{
				return ReadSt.getColumn(num).getString();
				cout << ReadSt.getColumn(num).getString() << endl;
			}
		}
		catch (const std::exception& ex)
		{
			ConTime = std::time(nullptr);
			fmt::print(fg(fmt::color::red),
				"[MocliaMusic {:%H:%M:%S} &err] {}\n",
				*localtime(&ConTime), ex.what());
		}
	}
}
