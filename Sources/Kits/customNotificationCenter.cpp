// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "Headers/Kits/customNotificationCenter.h"
#include "Headers/Kits/customLabel.h"
#include "Headers/Kits/cell_util.h"
#define CELL_DEBUG

#include <QLabel>

notificationCenter::notificationCenter(const QString &qss,QWidget *parent):
    customFrame(qss,parent),
    label_emptyNotifications(new customLabel(Cell_Const::QSS_CUSTOMLABEL,this)),
    label_hint(new customLabel(Cell_Const::QSS_CUSTOMLABEL,this)),
    processBlock(new customFrame(Cell_Const::QSS_CUSTOMFRAME,this)),
    label_WS(new QLabel(processBlock)),
    label_count(new QLabel(processBlock)),
    workshop_instancesCount(0)
{
    Init();
}

void notificationCenter::Init()
{
    label_emptyNotifications->setObjectName(QString::fromUtf8("label_emptyNotifications"));
    label_emptyNotifications->setText(tr("没有新的通知。"));
    label_emptyNotifications->setFont(QFont("微软雅黑 Light",18));
    label_emptyNotifications->setStyleSheet("color:rgb(255,255,255);");
    label_emptyNotifications->setGeometry(50, 100, label_emptyNotifications->width()+100,label_emptyNotifications->height());

    processBlock->setObjectName(QString::fromUtf8("processBlock"));
    processBlock->setGeometry(15,40,270,80);
    processBlock->setColor(Qt::white);
    processBlock->hide();

    label_WS->setObjectName(QString::fromUtf8("label_WS"));
    label_WS->setStyleSheet("background:transparent;border-image: url(:/images/Share/images/WS_process.png);");
    label_WS->setGeometry(20,25,108,30);

    label_count->setObjectName(QString::fromUtf8("label_count"));
    label_count->setGeometry(220,28,26,26);
    label_count->setText(QString::number(workshop_instancesCount));
    label_count->setFont(QFont("Courier New"));
    label_count->setStyleSheet("QLabel{color:rgb(70,70,70);}");

    label_hint->setObjectName(QString::fromUtf8("label_hint"));
    label_hint->setText(QString::fromUtf8("当前正在运行WorkShop实例。"));
    label_hint->setFont(QFont("Microsoft YaHei UI"));
    label_hint->setStyleSheet("QLabel{background:transparent; color:rgb(247,247,247);}");
    label_hint->setGeometry(20, 130, 250,20);
    label_hint->hide();
}

void notificationCenter::plusCnt()
{
    workshop_instancesCount++;
    label_count->setText(QString::number(workshop_instancesCount));
#ifdef CELL_DEBUG
    qDebug() << "The amount of workshops: " << workshop_instancesCount;
#endif
    if(workshop_instancesCount > 0){
        label_emptyNotifications->setWindowOpacity(0);
        label_emptyNotifications->hide();
        processBlock->show();
        CellGlobal::setFadeInOrOutAnimation(eff,animi,processBlock,300,CellGlobal::FADE_TYPE::_IN);
        label_hint->show();
        CellGlobal::setFadeInOrOutAnimation(eff,animi,label_hint,300,CellGlobal::FADE_TYPE::_IN);
    }
}

void notificationCenter::minusCnt()
{
    workshop_instancesCount--;
    label_count->setText(QString::number(workshop_instancesCount));
#ifdef CELL_DEBUG
    qDebug() << "The amount of workshops: " << workshop_instancesCount;
#endif
    if(workshop_instancesCount == 0){
        processBlock->setWindowOpacity(0);
        processBlock->hide();
        label_hint->setWindowOpacity(0);
        label_hint->hide();
        CellGlobal::setFadeInOrOutAnimation(eff,animi,label_emptyNotifications,300,CellGlobal::FADE_TYPE::_IN);
        label_emptyNotifications->show();
    }
}
