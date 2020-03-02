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
    explicit customGradientChangeFrame(const CellVariant &specialColor,QWidget *parent = nullptr);
    virtual ~customGradientChangeFrame() override = default;
    enum State{
        Normal,
        Special
    };
    void transCurrState(const customGradientChangeFrame::State &newState);

protected:
    State currState = Normal;
    QColor mSpecialColor;

public Q_SLOTS:
    virtual void setColorScheme(Cell::ColorScheme mode) override;
};

#endif // CUSTOMGRADIENTCHANGEFRAME_H
