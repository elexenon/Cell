// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef CUSTOMNOTIFICATIONCENTER_H
#define CUSTOMNOTIFICATIONCENTER_H

#include "customFrame.h"

class customLabel;
class QPropertyAnimation;
class QGraphicsOpacityEffect;
class QLabel;

class notificationCenter : public customFrame{
    Q_OBJECT
public:
    explicit notificationCenter(const QString &qss,QWidget *parent = nullptr);
    ~notificationCenter() override = default;

    void Init();

private:
    customLabel *label_emptyNotifications;    
    customLabel *label_hint;

    customFrame *processBlock;
    QLabel      *label_WS;
    QLabel      *label_count;

    unsigned workshop_instancesCount;

    QGraphicsOpacityEffect *eff;
    QPropertyAnimation     *animi;     

private slots:
    void plusCnt();
    void minusCnt();
};

#endif // CUSTOMNOTIFICATIONCENTER_H
