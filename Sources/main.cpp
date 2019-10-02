#include "Headers/mainwindow.h"
#include "Headers/_utility.h"

#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap(IMG_DIR+"SplashScreen.png");
    QSplashScreen startUp(pixmap);
    startUp.show();
    a.processEvents();

    mainWindow w;
    w.show();
    //startUp.finish(&w);
    return a.exec();
}
