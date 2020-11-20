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
			// ������Ҫ����
			int qq = 10000;
			string host = "127.0.0.1:8080", auth = "12345678", confirm = "y";

			// ��������
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
			cout << "��ӭʹ��MocliaMusic��������������г�ʼ�����á�" << endl;
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
				exit(0);
			}



			// �������������
#if defined(WIN32) || defined(_WIN32)
		// windows��������cls
			system("pause");
#else
		// linux��������clear
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
