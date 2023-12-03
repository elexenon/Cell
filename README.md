## A Qt Based Project
这是一个大学生创新项目的legacy代码仓库。

此项目使用了第三方开源文字编辑器 **QScintilla**, 其为 **Scintilla** 编辑器的Qt移植实现, 由 **Riverbank Computing Limited** 所持有, 他们的官方网站为:

<https://www.riverbankcomputing.com/software/qscintilla>

## Compile

### QScintilla

进入 <https://www.riverbankcomputing.com/software/qscintilla/download> 页面, 下载编辑器源码。

解压后，进入src目录, 双击项目文件 "QScintilla.pro"。

Qt会自动解析编辑器项目, 请选择 MinGW 64-bit 工具链, 然后同时将Debug和Release版本编译出来。

完成后，会得到两个动态链接库 "qscintilla2_qt5.dll" 以及 "qscintilla2_qt5d.dll" 。

最后，将这两个动态库放到一个合适的文件夹，将此文件夹路径复制到Cell_DeepLearning.pro对应位置即可。

### Sqlite3

进入sqlite官网 <https://sqlite.org/2021/sqlite-dll-win64-x64-3360000.zip> 下载预编译好的动态库，解压放置到之前创建好的那个“合适的文件夹”中。

## License

The GNU License(<http://www.gnu.org/licenses/gpl-3.0.html>)

## Preview
![image](https://github.com/Fijiisland/Cell_DeepLearning/blob/master/AppPreview/1.PNG)
![image](https://github.com/Fijiisland/Cell_DeepLearning/blob/master/AppPreview/2.PNG)
![image](https://github.com/Fijiisland/Cell_DeepLearning/blob/master/AppPreview/3.PNG)
![image](https://github.com/Fijiisland/Cell_DeepLearning/blob/master/AppPreview/4.png)
