// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "CellUI/Widgets/Launcher.h"

#include <QApplication>
#include <QSharedMemory>
#include <QMessageBox>
#include <QSplashScreen>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*
    QSharedMemory mem("Cell Launcher");
    if(!mem.create(1)){
        QMessageBox::information(nullptr, QObject::tr("提示:"), QObject::tr(CellUiConst::INSTANCE_IS_ON));
        return 0;
    }
    */
    // This operation is to register our custom property "COLOR_SCHEME".
    qRegisterMetaType<CellUiGlobal::COLOR_SCHEME>("COLOR_SCHEME");

    QPixmap pixmap(CellUiConst::IMG_DIR + QStringLiteral("cellSplashScreen.png"));

    QSplashScreen startUp(pixmap, Qt::WindowStaysOnTopHint);
    startUp.setFont(QFont(QStringLiteral("微软雅黑")));
    startUp.show();
    startUp.showMessage(QStringLiteral("装载模块"), Qt::AlignBottom | Qt::AlignHCenter, Qt::white);
    a.processEvents();
    startUp.showMessage(QStringLiteral("初始化主界面"), Qt::AlignHCenter | Qt::AlignBottom, Qt::white);

    Launcher w;
    w.setWindowTitle(QStringLiteral("Cell Launcher"));
    w.show();

    startUp.finish(&w);
    return a.exec();
}
