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
 *	Copyright (C) 2020 ����-STASWIT
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
 * ���ܣ������ļ�����
 * todo�������ļ���֤
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
			// ������Ҫ����
			int qq = 10000;
			string host = "127.0.0.1:8080", auth = "12345678", confirm = "y";

			// ��������
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
				"��ӭʹ��MocliaMusic��������������г�ʼ�����á�\n");
			cout << "���������Ļ�����QQ�˺ţ�";
			cin >> qq;
			cout << "����������MiraiAPIHttp��ַ������(127.0.0.1:8080)��";
			cin >> host;
			cout << "����������MiraiAPIHTTP AuthKey��";
			cin >> auth;
			cout << "��ȷ������������Ϣ��" << endl
				<< "�������˺ţ�"
				<< qq << endl
				<< "���ӵ�ַ��"
				<< host << endl
				<< "AuthKey��"
				<< auth << endl
				<< "ȷ��д�룿(y/n)��";
			cin >> confirm;



			if (confirm == "y")
			{
				// �������ݿ�
				db = nullptr;
				db = std::make_unique<SQLite::Database>("./BotConfig.db", OPEN_CREATE | OPEN_READWRITE);
				Transaction Tran(*db);
				// �������ݱ�
				db->exec("CREATE TABLE IF NOT EXISTS Program (number INTEAGER, bot_id INTEAGER, auth TEXT, ip_addr TEXT)");
				db->exec("CREATE TABLE IF NOT EXISTS Groups (group_id INTEAGER, bot_on BOOLEAN, default_service TEXT)");
				// д������
				Statement st(*db, "INSERT INTO Program (number, bot_id, auth, ip_addr) VALUES (1, ?, ?, ?)");
				st.bind(1, qq);
				st.bind(2, auth);
				st.bind(3, host);
				st.exec();
				// ȷ�ϸ���
				Tran.commit();
			}
			else
			{
				// �˳�
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
			// �������ݿ�
			db = nullptr;
			db = std::make_unique<SQLite::Database>("./BotConfig.db");
			// ��������
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
