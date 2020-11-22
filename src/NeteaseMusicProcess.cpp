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
 * ���ܣ����������ֵ��ģ������
 */
#undef byte

#include <iostream>
#include <string>

#include "NeteaseMusicProcess.h"
#include "JsonProcess.h"
#include "HttpProcess.h"

using namespace std;

string NeteaseMusic(string MuseName)
{
	string GetPost = HttpPost("http://music.163.com/api/search/pc", "s=" + 
		MuseName + "&limit=1&type=1");
	const char* Json = GetPost.c_str();

	if (JsonGetString(Json, "/result/songs/0/name") == "empty")
	{
		return "Music Not Found";
	}
	else
	{
		// ��������
		string UpMusicName = JsonGetString(Json, "/result/songs/0/name");
		const char* MusicName = UpMusicName.c_str();

		// ����
		string MusicArtist = JsonGetString(Json, "/result/songs/0/artists/0/name");

		// ˵������
		string UpDesc = MusicArtist + " - " + UpMusicName;
		const char* Desc = UpDesc.c_str();

		// ������Ƭ
		string UpPreview = JsonGetString(Json, "/result/songs/0/album/picUrl");
		const char* Preview = UpPreview.c_str();

		// ����id
		int MusicID = JsonGetInt(Json, "/result/songs/0/id");

		// ��ת��ַ
		string UpJumpURL = "https://music.163.com/#/song?id=" + to_string(MusicID);
		const char* JumpURL = UpJumpURL.c_str();

		// ���ŵ�ַ
		string UpMusicURL = "http://music.163.com/song/media/outer/url?id=" +
			to_string(MusicID) + ".mp3";
		const char* MusicURL = UpMusicURL.c_str();

		// ����json
		string ReturnJson = MusicJsonChange(MusicJson, Desc, JumpURL, MusicURL,
			Preview, MusicName, 1);
		return ReturnJson;
	}
}