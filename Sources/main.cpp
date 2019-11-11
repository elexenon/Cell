// Copyright 2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "Headers/mainwindow.h"

#include <QApplication>
#include <QSharedMemory>
#include <QMessageBox>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSharedMemory mem("Cell Launcher");
    if(!mem.create(1)){
        QMessageBox::information(nullptr, QObject::tr("提示:"), QObject::tr(CELL_UTIL::LITERAL::INSTANCE_IS_ON));
        return 0;
    }
    // This operation is to register our custom property "COLOR_SCHEME".
    qRegisterMetaType<COLOR_SCHEME>("COLOR_SCHEME");

    QPixmap pixmap(CELL_UTIL::LITERAL::IMG_DIR + QStringLiteral("SplashScreen.png"));

    QSplashScreen startUp(pixmap, Qt::WindowStaysOnTopHint);
    startUp.setFont(QFont(QStringLiteral("微软雅黑")));
    startUp.setFont(QFont(QStringLiteral("苹方-简")));
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
