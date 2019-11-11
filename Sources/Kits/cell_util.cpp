// Copyright 2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "Headers/Kits/cell_util.h"
#include "Headers/Kits/qstylesheetloader.hpp"

#include <QWidget>
#include <QDebug>
#include <QGraphicsEffect>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>

namespace CELL_UTIL {
namespace LITERAL {
const char* const INSTANCE_IS_ON("Cell Launcher is already running");
const QString IMG_DIR(":/images/Share/images/");
const QString FONT_DIR(":/fonts/Share/fonts/");
const QString STYLESHEET_DIR("C:\\Users\\HengyiYu\\Desktop\\Projects\\c++\\Qt\\Cell_DeepLearning\\Share\\styleSheets\\");
const QString LIB_DIR(":/libs/Share/libs/");
const QString COLOR_SPACE_GRAY("#798186");
const QColor COLOR_OPTION_BLOCK_DARK(44, 44, 45);
const QColor COLOR_OPTION_BLOCK_BRIGHT(218, 218, 218);
const QColor MAINWINDOW_DARK(31, 30, 31);
const QColor MAINWINDOW_BRIGHT(247, 247, 247);
} // namespace LITERAL{
} // namespace CELL_UTIL{

namespace CELL_UTIL{
namespace TOOLS{
QStyleSheetLoader *styleSheetLoader = new QStyleSheetLoader(CELL_UTIL::LITERAL::STYLESHEET_DIR);

void setDropShadowEffect(QList<QGraphicsDropShadowEffect*> animis,QList<QWidget*> modules,QPoint offset,QColor color,
                                int blurRadius)
{
    if(animis.size() != modules.size()){
        qDebug() << "The amount of animator is not equal to modules'.";
        return;
    }
    int len = animis.size();
    qDebug() << len;
    for(int i = 0; i < len;i++){
        animis[i] = new QGraphicsDropShadowEffect(modules[i]);
        animis[i]->setOffset(offset);
        animis[i]->setColor(color);
        animis[i]->setBlurRadius(blurRadius);
        modules[i]->setGraphicsEffect(animis[i]);
    }
}
void setPropertyAnimation(QList<QPropertyAnimation*> animis,QByteArray _property, QVariant s_value, QVariant e_value,
                                     int duration, QEasingCurve curve, QList<QWidget*> modules, QGraphicsEffect *effect)
{
    if(animis.size() != modules.size()){
        qDebug() << "The amount of animator is not equal to modules'.";
        return;
    }
    int cnt = animis.size();
    if(!effect){
        for(int i = 0;i < cnt;i ++){
            animis[i] = new QPropertyAnimation(modules[i], _property);
            animis[i]->setDuration(duration);
            animis[i]->setEasingCurve(curve);
            animis[i]->setStartValue(s_value);
            animis[i]->setEndValue(e_value);
            animis[i]->start(QAbstractAnimation::DeleteWhenStopped);
        }
    }
    else{
        animis[0] = new QPropertyAnimation(effect, _property);
        animis[0]->setDuration(duration);
        animis[0]->setEasingCurve(curve);
        animis[0]->setStartValue(s_value);
        animis[0]->setEndValue(e_value);
        animis[0]->start(QAbstractAnimation::DeleteWhenStopped);
    }
}
void multiModulesOneStyleSheet(QList<QWidget*> modules, QString qss)
{
    for(auto &e : modules)
        e->setStyleSheet(qss);
}
} // namespace TOOLS{
} // namespace CELL_UTIL{
