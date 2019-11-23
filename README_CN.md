# Cell_DeepLearning
### 一个基于Qt的项目

此项目在GPL V3.0许可约束下发布。

注意，CELL引入了一个开源文本编辑器 **QScintria**，它是由原版 **QScintria** 向Windows Qt移植的，以下是他们的官方网站：

<https://www.riverbankcomputing.com/software/qscintilla>

我们非常欣赏Riverbank的产品，因为Qscintria的工作得很好。

------------

### 编译

访问<https://www.riverbankcomputing.com/software/qscintria/downloadpage>，下载QScintria for windows。

解压QScintria源码包后，进入其子目录Qt4Qt5，然后双击项目文件“qscintria.pro”。

Qt将自动载入QScintria源代码，请选择MinGW 32位工具链，分别编译调试版本和发布版本。

之后，你将得到两个动态链接库 **“qscintria2_qt5.dll”** 和 **“qscintria2_qt5d.dll”**，它们分别对应于调试模式和发布模式。

差不多完成了，将这两个dll放到一个合适的目录中，并将它们添加到cell的pro文件中进行编译。
