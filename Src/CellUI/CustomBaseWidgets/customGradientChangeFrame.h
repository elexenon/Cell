// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef CUSTOMGRADIENTCHANGEFRAME_H
#define CUSTOMGRADIENTCHANGEFRAME_H

#include "customFrame.h"
#include "../../CellCore/Kits/CellUtility.h"

class QPropertyAnimation;

class customGradientChangeFrame : public customFrame{
    Q_OBJECT
public:
    explicit customGradientChangeFrame(const QString &qss,const QColor &specialColor,QWidget *parent = nullptr);
    ~customGradientChangeFrame() override = default;
    enum GRADIENT_STATE{
        _NORMAL,
        _SPECIAL
    };
    void transCurrState(const GRADIENT_STATE &newState);

protected:
    GRADIENT_STATE currState;
    CellUiGlobal::COLOR_SCHEME m_mode;
    QColor specialColor;

    QPropertyAnimation *animi;

public slots:
    void setColorScheme(CellUiGlobal::COLOR_SCHEME mode);
};

#endif // CUSTOMGRADIENTCHANGEFRAME_H
