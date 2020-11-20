#include <memory>
#include <iostream>
#include <string>
#include <map>
#include <regex>

#include <SQLiteCpp/SQLiteCpp.h>

#include <Configure.h>

using namespace std;
using namespace SQLite;

namespace MocliaMusic
{
	std::unique_ptr<SQLite::Database> db;

	void dbConnect()
	{
		try
		{
			db = nullptr;
			db = std::make_unique<SQLite::Database>("./BotConfig.mocdb", OPEN_CREATE | OPEN_READWRITE);
			configure();
		}
		catch (const std::exception& ex)
		{
			cout << "[MocliaMusic] " << ex.what() << endl;
		}
	}

	void configure()
	{
		try
		{
			// 创建必要变量
			int qq = 10000;
			string host = "127.0.0.1:8080", auth = "12345678", confirm = "y";

			// 初期配置
			cout << R"(
**********************************************************
*  __  __            _ _         __  __           _      *
* |  \/  |          | (_)       |  \/  |         (_)     *
* | \  / | ___   ___| |_  __ _  | \  / |_   _ ___ _  ___ *
* | |\/| |/ _ \ / __| | |/ _` | | |\/| | | | / __| |/ __|*
* | |  | | (_) | (__| | | (_| | | |  | | |_| \__ \ | (__ *
* |_|  |_|\___/ \___|_|_|\__,_| |_|  |_|\__,_|___/_|\___|*
*														 *
**********************************************************)" << endl;
			cout << "欢迎使用MocliaMusic，请根据引导进行初始化配置。" << endl;
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
				exit(0);
			}



			// 清屏，更换输出
#if defined(WIN32) || defined(_WIN32)
		// windows的命令是cls
			system("pause");
#else
		// linux的命令是clear
			system("clear");
#endif
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
			system("pause");
		}

	}

	string readconfig(string config)
	{
		try
		{
			db = nullptr;
			db = std::make_unique<SQLite::Database>("./BotConfig.mocdb");
			Statement ReadSt(*db, "SELECT ? FROM Program WHERE number = 1");
			ReadSt.bind(1, config);
			if (ReadSt.executeStep())
			{
				return ReadSt.getColumn(0).getString();
				cout << ReadSt.getColumn(0).getString() << endl;
			}
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
		}
	}
}
