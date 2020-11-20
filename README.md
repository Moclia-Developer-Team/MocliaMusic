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
    "qq":10000,// 机器人qq
    "authKey":""// mirai-api-http的authKey
}
~~~
随后双击MocliaMusic.exe运行即可。

#### 编译配置

本项目采用VCPKG进行第三方库管理，需要的库列表如下：
> Mirai-Cpp(需要另行安装)  
> cpr  
> RapidJson  
> SQLiteCpp  

请自行确认系统内是否有相关第三方库，否则将无法编译。

#### 其他

本项目目前仅在`windows x86_64`、`linux x64`、`raspberryPi 4B`编译测试通过。  
其他平台未测试，不保证原生兼容。  