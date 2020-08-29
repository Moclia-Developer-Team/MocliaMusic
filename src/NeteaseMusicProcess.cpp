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

	// 音乐名称
	string UpMusicName = JsonGetString(Json, "/result/songs/0/name");
	const char* MusicName = UpMusicName.c_str();

	// 歌手
	string MusicArtist = JsonGetString(Json, "/result/songs/0/artists/0/name");

	// 说明内容
	string UpDesc = MusicArtist + " - " + UpMusicName;
	const char* Desc = UpDesc.c_str();

	// 音乐照片
	string UpPreview = JsonGetString(Json, "/result/songs/0/album/picUrl");
	const char* Preview = UpPreview.c_str();

	// 音乐id
	int MusicID = JsonGetInt(Json, "/result/songs/0/id");

	// 跳转地址
	string UpJumpURL = "https://music.163.com/#/song?id=" + to_string(MusicID);
	const char* JumpURL = UpJumpURL.c_str();

	// 播放地址
	string UpMusicURL = "http://music.163.com/song/media/outer/url?id=" + 
		to_string(MusicID) + ".mp3";
	const char* MusicURL = UpMusicURL.c_str();

	// 返回json
	string ReturnJson = MusicJsonChange(MusicJson, Desc, JumpURL, MusicURL, 
		Preview, MusicName, 1);
	return ReturnJson;
}