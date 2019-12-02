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
#include "cell_util.h"

class customLabel;
class QPropertyAnimation;
class QGraphicsOpacityEffect;
class QLabel;

class notificationCenter : public customFrame{
    Q_OBJECT
public:
    explicit notificationCenter(const QString &qss,QWidget *parent = nullptr);
    ~notificationCenter() override = default;

    enum NOTIFI_STATE{_NORMAL,_BLUE};

    void     Init();
    inline
    unsigned getCurrWorkshopCount(){ return workshop_instancesCount;}

private:
    unsigned workshop_instancesCount;

    QGraphicsOpacityEffect *eff;
    QGraphicsOpacityEffect *eff2;
    QPropertyAnimation     *animi;
    QPropertyAnimation     *label_iden_animi;
    QPropertyAnimation     *label_ready_animi;
    QPropertyAnimation     *label_ready_animi_move;

    QLabel *label_ready;
    QLabel *label_identifi;
    QLabel *label_notifi;

    const QPoint hidePos_iden;
    const QPoint normalPos_iden;
    const QPoint hidePos_ready;
    const QPoint normalPos_ready;

    NOTIFI_STATE currState;
    CellGlobal::COLOR_SCHEME m_mode;

    void transCurrState(const NOTIFI_STATE &newState);

private slots:
    void setColorScheme(CellGlobal::COLOR_SCHEME mode);
    void plusCnt();
    void minusCnt();
};

#endif // CUSTOMNOTIFICATIONCENTER_H
