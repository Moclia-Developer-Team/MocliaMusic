#include <iostream>
#include <string>
#include <map>
#include <cstdio>

#include <rapidjson/document.h>
#include <rapidjson/pointer.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/filereadstream.h>

#include "JsonProcess.h"

using namespace std;
using namespace rapidjson;

string JsonReaderString(char* Path, char* point)
{
#ifdef _WIN32
    FILE* Filep = fopen(Path, "rb");
    if (!Filep)
    {
        Filep = fopen(Path, "wb");
    }
#else
    FILE* Filep = fopen(Path, "r");
    if (!Filep)
    {
        Filep = fopen(Path, "w");
    }
#endif // _WIN32

    char readBuffer[65536];
    FileReadStream read(Filep, readBuffer, sizeof(readBuffer));

    Document d;
    d.ParseStream(read);

    Value* v = Pointer(point).Get(d);
    if (v == nullptr)
    {
        return "empty";
    }
    else
    {
        return v->GetString();
    }
    fclose(Filep);
}

int JsonReaderInt(char* Path, char* point)
{
#ifdef _WIN32
    FILE* Filep = fopen(Path, "rb");
    if (!Filep)
    {
        Filep = fopen(Path, "wb");
    }
#else
    FILE* Filep = fopen(Path, "r");
    if (!Filep)
    {
        Filep = fopen(Path, "w");
    }
#endif // _WIN32

    char readBuffer[65536];
    FileReadStream read(Filep, readBuffer, sizeof(readBuffer));

    Document d;
    d.ParseStream(read);

    Value* v = Pointer(point).Get(d);
    if (v == nullptr)
    {
        return -1;
    }
    else
    {
        return v->GetInt();
    }
    fclose(Filep);
}

// json数据处理，传出string
string JsonGetString(const char* Json, char* Path)
{
	StringStream JsonStream(Json); // 创建输入流，给RapidJson传递json原始数据
	Document JsonDOM; // 创建RapidJson DOM
	JsonDOM.ParseStream(JsonStream); // 分析json原始数据并传入DOM
	Value* JsonValue =  Pointer(Path).Get(JsonDOM); // 获取对应路径的值，并返回
	return JsonValue->GetString();
}

// json数据处理，传出int
int JsonGetInt(const char* Json, char* Path)
{
	StringStream JsonStream(Json); // 创建输入流，给RapidJson传递json原始数据
	Document JsonDOM; // 创建RapidJson DOM
	JsonDOM.ParseStream(JsonStream); // 分析json原始数据并传入DOM
	Value* JsonValue = Pointer(Path).Get(JsonDOM); // 获取对应路径的值，并返回
	return JsonValue->GetInt();
}

// 改变输出音乐的json
string MusicJsonChange(
    const char* Json, const char* Desc, const char* Jumpurl,
    const char* MusicUrl, const char* Preview, const char* Title, int MuseType)
{
    // 音乐服务提供商
    map<int, const char*> MusicType = {
        {1,"网易云音乐"},
        {2,"QQ音乐"},
        {3,"酷狗音乐"}
    };

    string MuseTitle = Title;
    string MType = MusicType[MuseType];
    string UpPrompt = "[分享][" + MuseTitle + "] - " + MType;
    const char* Prompt = UpPrompt.c_str();

    StringStream JsonStream(Json);
    Document JsonDOM;
    JsonDOM.ParseStream(JsonStream);
    
    Value MusicDesc, MusicMuseUrl, MusicJumpUrl,
        MusicPreview, MusicTitle, MusicMuseType, MusicPrompt;
    MusicDesc.SetString(StringRef(Desc)); // 介绍信息
    MusicMuseUrl.SetString(StringRef(MusicUrl)); // 播放地址
    MusicJumpUrl.SetString(StringRef(Jumpurl)); // 跳转地址
    MusicPreview.SetString(StringRef(Preview)); // 专辑图片
    MusicTitle.SetString(StringRef(Title)); // 曲名
    MusicMuseType.SetString(StringRef(MusicType[MuseType])); // 提供商
    MusicPrompt.SetString(StringRef(Prompt));

    // 内容替换
    Pointer("/meta/music/desc").Swap(JsonDOM, MusicDesc);
    Pointer("/meta/music/jumpUrl").Swap(JsonDOM, MusicJumpUrl);
    Pointer("/meta/music/musicUrl").Swap(JsonDOM, MusicMuseUrl);
    Pointer("/meta/music/preview").Swap(JsonDOM, MusicPreview);
    Pointer("/meta/music/title").Swap(JsonDOM, MusicTitle);
    Pointer("/meta/music/tag").Swap(JsonDOM, MusicMuseType);
    Pointer("/prompt").Swap(JsonDOM, MusicPrompt);

    StringBuffer JsonOut;
    Writer<StringBuffer> writer(JsonOut);
    JsonDOM.Accept(writer);
    string Out = JsonOut.GetString();
    return Out;
}

const char* MusicJson = R"(
{
"app": "com.tencent.structmsg",
"config": {
    "autosize": true,
    "ctime": 0,
    "forward": true,
    "token": "6a2658ee487631c2c2d77aa583792dc1",
    "type": "normal"
},
"desc": "音乐",
"meta": {
    "music": {
        "action": "",
        "android_pkg_name": "",
        "app_type": 1,
        "appid": 100497308,
        "desc": "",
        "jumpUrl": "",
        "musicUrl": "",
        "preview": "",
        "sourceMsgId": 0,
        "source_icon": "",
        "source_url": "",
        "tag": "",
        "title": ""
    }
},
"prompt": "",
"ver": "0.0.0.1",
"view": "music"
}
)";