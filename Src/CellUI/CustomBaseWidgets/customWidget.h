// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
//
// This class implemented dropshadow effect & "color" custom property & qss override
#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>

#include "CellWidgetGlobalInterface.h"
#include "CellWinstyleWidget.h"
#include "../../CellCore/Kits/CustomCppInterfaceDefination.h"

class customWidget : public CellWinstyleWidget
{
    Q_PROPERTY(QColor color READ color WRITE setColor)
public:
    explicit customWidget(QWidget *parent = nullptr);

    virtual void setColor(const QColor &color) override;
};
#endif
