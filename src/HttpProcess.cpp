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
 * 功能：点歌的json请求
 */

#include <iostream>
#include <string>
#include <ctime>

#include <cpr/cpr.h>
#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/chrono.h>

using namespace std;
using namespace cpr;
using namespace std::literals::chrono_literals;

time_t HttpTime;

//暂时用不到Get
/*string HttpGet(string URL)
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
}*/

string HttpPost(string URL, string PostBody)
{
	try
	{
		Response URLPost = Post(Url{ URL }, Body{ PostBody });
		return URLPost.text;
	}
	catch (const std::exception& ex)
	{
		HttpTime = time(nullptr);
		fmt::print(fg(fmt::color::red),
			"[MocliaMusic {:%H:%M:%S} &err] {}\n",
			*localtime(&HttpTime), ex.what());
	}
}