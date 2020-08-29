### MocliaMusic，一个基于mirai-cpp和mirai-api-http的点歌插件

> 目前仅支持网易云音乐，其他音乐服务将在未来添加。

#### 使用说明

`*MusicHelp` MocliaMusic的帮助页面。
~网易点歌[曲名]~在网易云进行点歌

#### 运行前配置

在同目录下的BotConfig.json下填写以下内容
~~~
//在正式使用中注释必须删除。
{
    "host":"", //你的mirai-api-http ip地址
    "port":, // mirai-api-http的端口号
    "qq":"10000_qq",// 机器人qq，后面必须加_qq
    "authKey":""// mirai-api-http的authKey
}
~~~
随后双击MocliaMusic.exe运行即可。

#### 编译配置

本项目采用VCPKG和Git Submodule进行第三方库管理，需要的库列表如下：

> git submodule:  
> > Mirai-Cpp  

> vcpkg:  
> > cpr  
> > RapidJson  

请自行确认系统内是否有相关第三方库，否则将无法编译。

#### 其他

本项目目前仅在windows x86_64编译通过，其他系统因vcpkg原因暂未测试，将在未来适配。