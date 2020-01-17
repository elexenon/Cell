// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
//
// This class implemented "color" custom property.
#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QLabel>

#include "CellWidgetGlobalInterface.h"
#include "../../CellCore/Kits/CustomCppInterfaceDefination.h"

class customLabel : public QLabel, implements CellWidgetGlobalInterface
{
    Q_OBJECT
    const QString BASEQSS;
public:
    explicit customLabel(const QString &qss, QWidget *parent = nullptr);
    ~customLabel() = default;

public:
    virtual void setColor(const QColor &color) override;
    virtual void setColorScheme(CellUiGlobal::COLOR_SCHEME mode) override;
};
#endif // CUSTOMLABEL_H
