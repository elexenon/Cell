#include "Headers/mainwindow.h"

#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<COLOR_SCHEME>("COLOR_SCHEME");
    QPixmap pixmap(IMG_DIR + QStringLiteral("SplashScreen.png"));
    QSplashScreen startUp(pixmap, Qt::WindowStaysOnTopHint);
#ifdef Q_OS_WIN32
    startUp.setFont(QFont(QStringLiteral("微软雅黑")));
#elif defined (__APPLE__)
    startUp.setFont(QFont(QStringLiteral("苹方-简")));
#endif
    startUp.show();
    startUp.showMessage(QStringLiteral("装载模块"), Qt::AlignBottom | Qt::AlignHCenter, Qt::white);
    a.processEvents();
    startUp.showMessage(QStringLiteral("初始化主界面"), Qt::AlignHCenter | Qt::AlignBottom, Qt::white);
    mainWindow w;
    w.setWindowTitle(QStringLiteral("Cell Launcher"));
    w.show();
    startUp.finish(&w);
    return a.exec();
}
