// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customNotificationCenter.h"

#include <QLabel>

#define CELL_DEBUG

notificationCenter::notificationCenter(QWidget *parent):
    customGradientChangeFrame(QColor(79,147,184),parent),
    workshop_instancesCount(0),
    label_ready(new QLabel(this)),
    label_identifi(new QLabel(this)),
    label_notifi(new QLabel(this)),
    hidePos_iden(QPoint(-120,3)),
    normalPos_iden(QPoint(10,3)),
    hidePos_ready(QPoint(130,3)),
    normalPos_ready(QPoint(10,3))
{
    Init();
}

void notificationCenter::Init()
{
    label_identifi->setText(CHAR2STR("WORKSHOP"));
    label_identifi->setFont(QFont (CHAR2STR("Microsoft YaHei UI"), 8, QFont::Bold));
    label_identifi->setStyleSheet("QLabel{color:rgb(255,255,255);}");
    label_identifi->move(-120,0);

    label_ready->setText(QString::fromUtf8("就绪"));
    label_ready->setFont(CellUiGlobal::getFont(CHAR2STR("Microsoft YaHei UI"), 14));
    label_ready->setStyleSheet("QLabel{color:rgb(255,255,255);}");
    label_ready->move(10,0);
}

void notificationCenter::plusCnt()
{
    if(currState != GRADIENT_STATE::_SPECIAL){
        transCurrState(GRADIENT_STATE::_SPECIAL);
        CellUiGlobal::setPropertyAnimation({animi},
                                         "pos",
                                         label_identifi->pos(),
                                         normalPos_iden,
                                         700,
                                         QEasingCurve::InOutCubic,
                                         {label_identifi},nullptr);
        CellUiGlobal::setFadeInOrOutAnimation(eff,label_ready_animi,
                                            label_ready,700,CellUiGlobal::FADE_TYPE::_OUT);
        CellUiGlobal::setFadeInOrOutAnimation(eff2,label_iden_animi,
                                            label_identifi,700,CellUiGlobal::FADE_TYPE::_IN);
        CellUiGlobal::setPropertyAnimation({label_ready_animi_move},
                                         "pos",
                                         label_ready->pos(),
                                         hidePos_ready,
                                         700,
                                         QEasingCurve::InOutCubic,
                                         {label_ready},nullptr);
    }
    workshop_instancesCount++;
#ifdef CELL_DEBUG
    qDebug() << "--------------------------";
    qDebug() << "NOTIFICATIONCENTER";
    qDebug() << "The amount of workshops: " << workshop_instancesCount;
    qDebug() << "--------------------------\n";
#endif
}

void notificationCenter::minusCnt()
{
    if(--workshop_instancesCount == 0){
        transCurrState(GRADIENT_STATE::_NORMAL);
        CellUiGlobal::setPropertyAnimation({animi},
                                         "pos",
                                         label_identifi->pos(),
                                         hidePos_iden,
                                         700,
                                         QEasingCurve::InOutCubic,
                                         {label_identifi},nullptr);
        CellUiGlobal::setFadeInOrOutAnimation(eff,label_ready_animi,
                                            label_ready,700,CellUiGlobal::FADE_TYPE::_IN);
        CellUiGlobal::setFadeInOrOutAnimation(eff2,label_iden_animi,
                                            label_identifi,700,CellUiGlobal::FADE_TYPE::_OUT);
        CellUiGlobal::setPropertyAnimation({label_ready_animi_move},
                                         "pos",
                                         label_ready->pos(),
                                         normalPos_ready,
                                         700,
                                         QEasingCurve::InOutCubic,
                                         {label_ready},nullptr);

    }
#ifdef CELL_DEBUG
    qDebug() << "--------------------------";
    qDebug() << "NOTIFICATIONCENTER";
    qDebug() << "The amount of workshops: " << workshop_instancesCount;
    qDebug() << "--------------------------\n";
#endif
}
