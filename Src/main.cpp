// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "CellUI/Widgets/Launcher.h"

#include <QApplication>
#include <QSharedMemory>
#include <QMessageBox>
#include <QSplashScreen>
#include <iostream>

#define SPLASHSCREEN

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
    // This operation is to register our custom property "ColorScheme".
    qRegisterMetaType<Cell::ColorScheme>("ColorScheme");
    qRegisterMetaType<Cell::ColorScheme>("ColorScheme&");

    QPixmap pixmap(CellUiLiteral::IMG_DIR + QStringLiteral("cellSplashScreen.png"));
#ifdef SPLASHSCREEN
    QSplashScreen startUp(pixmap, Qt::WindowStaysOnTopHint);
    startUp.setFont(QFont(QStringLiteral("微软雅黑")));
    startUp.show();
    startUp.showMessage(QStringLiteral("装载模块"), Qt::AlignBottom | Qt::AlignHCenter, QColor(100, 100, 100));
#endif
    a.processEvents();
#ifdef SPLASHSCREEN
    startUp.showMessage(QStringLiteral("初始化主界面"), Qt::AlignHCenter | Qt::AlignBottom, QColor(100, 100, 100));
#endif
    Launcher w;
    w.setWindowTitle(QStringLiteral("Cell Launcher"));
    w.show();
#ifdef SPLASHSCREEN
    startUp.finish(&w);
#endif
    return a.exec();
}
