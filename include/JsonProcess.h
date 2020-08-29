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
 *	Copyright (C) 2020 ÐÇÁ›-STASWIT
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
 */
#include <iostream>
#include <string>

#include <rapidjson/document.h>
#include <rapidjson/pointer.h>

using namespace std;
using namespace rapidjson;

string JsonGetString(const char* Json, char* Path);
int JsonGetInt(const char* Json, char* Path);
string MusicJsonChange(
    const char* Json, const char* Desc, const char* Jumpurl,
    const char* MusicUrl, const char* Preview, const char* Title, int MuseType);
string JsonReaderString(char* Path, char* point);
int JsonReaderInt(char* Path, char* point);
extern const char* MusicJson;