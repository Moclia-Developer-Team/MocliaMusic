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