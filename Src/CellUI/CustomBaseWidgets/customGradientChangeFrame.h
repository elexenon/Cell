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

class customGradientChangeFrame : public customFrame{
    Q_OBJECT
public:
    explicit customGradientChangeFrame(const QColor &specialColor,QWidget *parent = nullptr);
    virtual ~customGradientChangeFrame() override = default;
    enum GRADIENT_STATE{
        _NORMAL,
        _SPECIAL
    };
    void transCurrState(const GRADIENT_STATE &newState);

protected:
    GRADIENT_STATE currState = GRADIENT_STATE::_NORMAL;
    QColor specialColor;

public slots:
    virtual void setColorScheme(CellUiGlobal::COLOR_SCHEME mode) override;
};

#endif // CUSTOMGRADIENTCHANGEFRAME_H
