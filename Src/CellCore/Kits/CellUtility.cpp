// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "CellUtility.h"
#include "textFileLoader.hpp"
#include "CellGlobalMacros.h"

#include <QWidget>
#include <QFrame>
#include <QDebug>
#include <QGraphicsEffect>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QLabel>
#include <QFontDatabase>
#define DEBUG

namespace CellUiLiteral {
const char* const INSTANCE_IS_ON("Cell Launcher is already running");
const QString IMG_DIR(":/images/Images/");
const QString FONT_DIR(":/fonts/Fonts/");
const QString STYLESHEET_DIR("C:\\Users\\HengyiYu\\Desktop\\Projects\\c++\\Qt\\Cell_DeepLearning\\CellResourcesFiles\\StyleSheets\\");
} // namespace CellUiLiteral{

namespace CellUiGlobal{
textFileLoader &loader = textFileLoader::instance(CellUiLiteral::STYLESHEET_DIR);
void setDropShadowEffect(QList<QGraphicsDropShadowEffect*> animis,const QList<QWidget*> &modules,
                                     const QPoint &offset,const QColor &color,int blurRadius)
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
void setPropertyAnimation(QList<QPropertyAnimation*> &&animis,const QByteArray &_property, const QVariant &s_value,
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
                             int duration, CellUiGlobal::FADE_TYPE type){
    int startValue = 0, endValue = 1;
    if(type == CellUiGlobal::FADE_TYPE::_OUT)
        qSwap(startValue, endValue);
    eff = new QGraphicsOpacityEffect(target);
    eff->setOpacity(startValue);
    target->setGraphicsEffect(eff);
    CellUiGlobal::setPropertyAnimation({animi}, "opacity", startValue, endValue, duration,
                         QEasingCurve::Linear, {nullptr}, eff);
}
QFrame* getLine(CellUiGlobal::LINE_TYPE type){
    QFrame *tmp = new QFrame;
    type == CellUiGlobal::LINE_TYPE::HLine ? tmp->setFixedHeight(1)
                                           : tmp->setFixedWidth(1);
    tmp->setStyleSheet(CHAR2STR("QFrame{color:rgb(180,180,180);}"));
    tmp->setFrameShadow(QFrame::Plain);
    tmp->setFrameShape(static_cast<QFrame::Shape>(type));
    return tmp;
}
QFont getFont(const QString &fontName, int pixelSize){
    bool fontExists = false;
    QFontDatabase fontDatabase;
    foreach(const QString &family, fontDatabase.families()){
        if(family == fontName){
            fontExists = true;
            break;
        }
    }
    if(fontExists){
        QFont tmp(fontName);
        tmp.setPixelSize(pixelSize);
        return tmp;
    }
    int fontID = QFontDatabase::addApplicationFont(CellUiLiteral::FONT_DIR + fontName);
    QFont tmp(QFontDatabase::applicationFontFamilies(fontID).at(0));
    tmp.setPixelSize(pixelSize);
    return tmp;
}
void setCustomTextLabel(QLabel *label, const QString& fontName, int fontPixelSize, const QString& text){
    label->setFont(getFont(fontName, fontPixelSize));
    if(text == CMPSTR(" ")) return;
    label->setText(text);
}
void setLabelPixmap(QLabel *label, const QString& fileName, int iconWidth, int iconHeight){
    QPixmap newPixmap;
    newPixmap.load(CellUiLiteral::IMG_DIR + fileName);
    newPixmap = newPixmap.scaled(iconWidth, iconHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    label->setPixmap(newPixmap);
    label->setStyleSheet(("QLabel{background:transparent;}"));
}
} // namespace CellUiGlobal{
