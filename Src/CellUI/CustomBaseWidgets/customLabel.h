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
#include "../../CellCore/Kits/CellGlobalMacros.h"

class customLabel : public QLabel, implements CellWidgetGlobalInterface
{
    friend class customListButton;
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
public:
    explicit customLabel(QWidget *parent = nullptr);
    virtual ~customLabel() override = default;

protected:
    //! Inhrited from
    //! CellWidgetGlobalInterface.
    virtual void
    init() override;

    inline virtual void
    setEventConnections() override {};

    virtual void
    setColor(const QColor &color) override;

    virtual void
    setAnimiStartEndColor(Cell::ColorScheme mode, QColor &startColor, QColor &endColor) override;

    virtual void
    changeToColor(const QColor &startColor, const QColor &targetColor, int duration) override;

public Q_SLOTS:
    virtual void
    setColorScheme(Cell::ColorScheme mode) override;
};
#endif // CUSTOMLABEL_H
