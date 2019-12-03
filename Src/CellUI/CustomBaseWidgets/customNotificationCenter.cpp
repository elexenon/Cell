// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customNotificationCenter.h"
#include "customLabel.h"
#define CELL_DEBUG

#include <QLabel>

notificationCenter::notificationCenter(const QString &qss,QWidget *parent):
    customFrame(qss,parent),
    workshop_instancesCount(0),
    label_ready(new QLabel(this)),
    label_identifi(new QLabel(this)),
    label_notifi(new QLabel(this)),
    hidePos_iden(QPoint(-120,3)),
    normalPos_iden(QPoint(10,3)),
    hidePos_ready(QPoint(130,3)),
    normalPos_ready(QPoint(10,3)),
    currState(NOTIFI_STATE::_NORMAL),
    m_mode(CellGlobal::COLOR_SCHEME::_BRIGHT)
{
    Init();
}

void notificationCenter::Init()
{
    label_identifi->setObjectName("label_identifi");
    label_identifi->setText("WORKSHOP");
    label_identifi->setFont(QFont ("Microsoft YaHei UI",8,QFont::Bold));
    label_identifi->setStyleSheet("QLabel{color:rgb(255,255,255);}");
    label_identifi->setGeometry(-120,3,120,22);

    label_ready->setObjectName("label_ready");
    label_ready->setText(QString::fromUtf8("就绪"));
    label_ready->setFont(QFont("Microsoft YaHei UI",9));
    label_ready->setStyleSheet("QLabel{color:rgb(255,255,255);}");
    label_ready->setGeometry(10,3,40,22);
}

void notificationCenter::transCurrState(const NOTIFI_STATE &newState)
{
    if(newState == currState) return;
    currState = newState;
    const QColor targetColor = (newState == NOTIFI_STATE::_BLUE ? QColor(50,200,230) :
                                (m_mode == CellGlobal::COLOR_SCHEME::_BRIGHT ? Cell_Const::GRAYLEVEL218 : Cell_Const::GRAYLEVEL70));
    CellGlobal::setPropertyAnimation({animi},
                                     "color",
                                     color(),
                                     targetColor,
                                     800,
                                     QEasingCurve::InOutCubic,
    {this},nullptr);
}

void notificationCenter::setColorScheme(CellGlobal::COLOR_SCHEME mode)
{
    if(mode == m_mode) return;
    m_mode = mode;
    if(currState == NOTIFI_STATE::_BLUE) return;
    const QColor targetColor = (mode == CellGlobal::COLOR_SCHEME::_BRIGHT ? Cell_Const::GRAYLEVEL218 : Cell_Const::GRAYLEVEL70);
    CellGlobal::setPropertyAnimation({animi},
                                     "color",
                                      color(),
                                      targetColor,
                                      CellGlobal::CELL_GLOBALANIMIDURATION,
                                      QEasingCurve::InOutCubic,
                                      {this}, nullptr);
}

void notificationCenter::plusCnt()
{
    if(currState != NOTIFI_STATE::_BLUE){
        transCurrState(NOTIFI_STATE::_BLUE);
        CellGlobal::setPropertyAnimation({animi},
                                         "pos",
                                         label_identifi->pos(),
                                         normalPos_iden,
                                         700,
                                         QEasingCurve::InOutCubic,
                                         {label_identifi},nullptr);
        CellGlobal::setFadeInOrOutAnimation(eff,label_ready_animi,
                                            label_ready,700,CellGlobal::FADE_TYPE::_OUT);
        CellGlobal::setFadeInOrOutAnimation(eff2,label_iden_animi,
                                            label_identifi,700,CellGlobal::FADE_TYPE::_IN);
        CellGlobal::setPropertyAnimation({label_ready_animi_move},
                                         "pos",
                                         label_ready->pos(),
                                         hidePos_ready,
                                         700,
                                         QEasingCurve::InOutCubic,
                                         {label_ready},nullptr);
    }
    workshop_instancesCount++;
#ifdef CELL_DEBUG
    qDebug() << "The amount of workshops: " << workshop_instancesCount;
#endif
}

void notificationCenter::minusCnt()
{
    if(--workshop_instancesCount == 0){
        transCurrState(NOTIFI_STATE::_NORMAL);
        CellGlobal::setPropertyAnimation({animi},
                                         "pos",
                                         label_identifi->pos(),
                                         hidePos_iden,
                                         700,
                                         QEasingCurve::InOutCubic,
                                         {label_identifi},nullptr);
        CellGlobal::setFadeInOrOutAnimation(eff,label_ready_animi,
                                            label_ready,700,CellGlobal::FADE_TYPE::_IN);
        CellGlobal::setFadeInOrOutAnimation(eff2,label_iden_animi,
                                            label_identifi,700,CellGlobal::FADE_TYPE::_OUT);
        CellGlobal::setPropertyAnimation({label_ready_animi_move},
                                         "pos",
                                         label_ready->pos(),
                                         normalPos_ready,
                                         700,
                                         QEasingCurve::InOutCubic,
                                         {label_ready},nullptr);

    }
#ifdef CELL_DEBUG
    qDebug() << "The amount of workshops: " << workshop_instancesCount;
#endif
}
