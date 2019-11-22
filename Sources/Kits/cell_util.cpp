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
#include <QGraphicsOpacityEffect>
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

const QString QSS_CUSTOMFRAME_WITH_RADIUS(
"QFrame{"
"border-radius:5px; "
"background-color: rgb(%1, %2, %3);"
"}");
const QString QSS_CUSTOMFRAME(
"QFrame{"
"background-color: rgb(%1, %2, %3);"
"}");
const QString QSS_CUSTOMLABEL(
"QLabel{"
"color: rgb(%1, %2, %3);"
"}");
const QString QSS_CUSTOMBUTTON_STATIC(
"QPushButton{"
"background-color: rgb(%1, %2, %3);"
"border: 0px solid gray;"
"}"
"QPushButton:hover{"
"background-color: rgb(%4, %5, %6);"
"border: 0px solid gray;"
"}"
"QPushButton:checked{"
"background-color: rgb(%7, %8, %9);"
"border: 0px solid gray;"
"}");
const QString QSS_CUSTOMBUTTON_DYNAMIC(
"QPushButton{"
"background-color: rgb(%1, %2, %3);"
"border: 1px solid gray;"
"}"
"QPushButton:checked{"
"background-color: rgb(%4, %5, %6);"
"border: 1px solid gray;"
"}");
} // namespace LITERAL{
} // namespace CELL_UTIL{

namespace CELL_UTIL{
namespace TOOLS{
QStyleSheetLoader *styleSheetLoader = new QStyleSheetLoader(CELL_UTIL::LITERAL::STYLESHEET_DIR);

void setDropShadowEffect(QList<QGraphicsDropShadowEffect*> animis,const QList<QWidget*> &modules,
                         const QPoint &offset,const QColor &color,
                                int blurRadius)
{
    if(animis.size() != modules.size()){
        qDebug() << "The amount of animator is not equal to modules'.";
        return;
    }
    int len = animis.size();
    for(int i = 0; i < len;i++){
        animis[i] = new QGraphicsDropShadowEffect(modules[i]);
        animis[i]->setOffset(offset);
        animis[i]->setColor(color);
        animis[i]->setBlurRadius(blurRadius);
        modules[i]->setGraphicsEffect(animis[i]);
    }
}
void setPropertyAnimation(QList<QPropertyAnimation*> animis,const QByteArray &_property, const QVariant &s_value,
                          const QVariant &e_value,int duration, QEasingCurve curve, const QList<QWidget*> &modules, QGraphicsEffect *effect)
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
void multiModulesOneStyleSheet(const QList<QWidget*> &modules, const QString &qss)
{
    for(auto &e : modules)
        e->setStyleSheet(qss);
}
void setFadeInOrOutAnimation(QGraphicsOpacityEffect *eff,QPropertyAnimation *animi,QWidget *target,
                             int duration, FADE_TYPE type){
    int startValue = 0, endValue = 1;
    if(type == FADE_TYPE::_OUT)
        qSwap(startValue, endValue);
    eff = new QGraphicsOpacityEffect(target);
    eff->setOpacity(startValue);
    target->setGraphicsEffect(eff);
    TOOLS::setPropertyAnimation({animi}, "opacity", startValue, endValue, duration,
                         QEasingCurve::Linear, {nullptr}, eff);
}
} // namespace TOOLS{
} // namespace CELL_UTIL{
