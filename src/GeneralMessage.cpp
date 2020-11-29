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
#include <string>
#include <map>

#include "GeneralMessage.h"

using namespace std;

/*bot版本信息*/
string BotHelp()
{
	// 版本号
	const string MocMuse_Ver = "2.0.1 Release ";
	// 标头信息
	const string MocMuse_Info = "MocliaMusic by STASWIT Version"
		+ MocMuse_Ver;
	// 平台
	const string Platform = "for Mirai-Http";
	string CI;
	// 编译信息
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
	// 帮助列表
	const string MocHelp = "可用指令：\n网易点歌[歌名]";
	string Reply = MocMuse_FullInfo + "\n" + MocHelp;
	return Reply;
}