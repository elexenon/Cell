// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef CUSTOMNOTIFICATIONCENTER_H
#define CUSTOMNOTIFICATIONCENTER_H

#include "customSwitchFrame.h"

class QPropertyAnimation;
class QGraphicsOpacityEffect;
class QLabel;

class notificationCenter : public customSwitchFrame{
friend class Launcher;
    Q_OBJECT
public:
    explicit notificationCenter(QWidget *parent = nullptr);
    ~notificationCenter() override = default;

    virtual void
    init() override;

    inline unsigned
    getCurrWorkshopCount(){ return workshop_instancesCount;}

private:
    unsigned workshop_instancesCount;

    QGraphicsOpacityEffect *eff;
    QGraphicsOpacityEffect *eff2;
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

private Q_SLOTS:
    void
    plusCnt();

    void
    minusCnt();
};

#endif // CUSTOMNOTIFICATIONCENTER_H
