### MocliaMusic，一个基于mirai-cpp和mirai-api-http的点歌插件

> 目前仅支持网易云音乐，其他音乐服务将在未来添加。

#### 使用说明

消息端指令：  
`*MusicHelp` MocliaMusic的帮助页面。  
`网易点歌[曲名]`在网易云进行点歌。  
ps:@某个机器人可以指定机器人进行点歌。  

服务端指令：  
`about` MocliaMusic的帮助页面。
`stop` 结束运行。  

#### 初次运行配置

~~~
// 在控制台根据提示填入以下内容：
机器人的QQ号：如10000
MiraiAPIHttp的ip地址和端口：如127.0.0.1:2020
MiraiAPIHttp的Auth密码：如123456
// 确认信息后你就可以正常使用了。

~~~

#### 编译配置

本项目采用VCPKG进行第三方库管理，需要的库列表如下：
> Mirai-Cpp(需要另行安装)  
> cpr  
> RapidJson  
> SQLiteCpp  
> fmt

请自行确认系统内是否有相关第三方库，否则将无法编译。

#### 其他

本项目目前仅在`windows x86_64`、`linux x64`、`raspberryPi 4B`编译测试通过。  
其他平台未测试，不保证原生兼容。  