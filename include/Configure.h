#include <iostream>
#include <string>
#include <memory>

#include <SQLiteCpp/SQLiteCpp.h>

using namespace std;

namespace MocliaMusic
{
	extern std::unique_ptr<SQLite::Database> db;
	void dbConnect();
	void configure();
	string readconfig(string config);
}