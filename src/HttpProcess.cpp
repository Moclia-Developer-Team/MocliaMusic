#include <iostream>
#include <string>

#include <cpr/cpr.h>

using namespace std;
using namespace cpr;

string HttpGet(string URL)
{
	try
	{
		Response URLGet = Get(Url{URL});
		return URLGet.text;
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << endl;
	}
}

string HttpPost(string URL, string PostBody)
{
	try
	{
		Response URLPost = Post(Url{ URL }, Body{ PostBody });
		return URLPost.text;
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << endl;
	}
}