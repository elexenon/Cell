// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef CUSTOMPAGESWITCHBTN_H
#define CUSTOMPAGESWITCHBTN_H

#include <QPushButton>

#include "CellWidgetGlobalInterface.h"
#include "../../CellCore/Kits/CellGlobalMacros.h"

class customStaticButton : public QPushButton, implements CellWidgetGlobalInterface{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
    const QString BASEQSS;
public:
    explicit customStaticButton(QWidget *parent = nullptr);
    ~customStaticButton() override = default;

    void         setBrightModeCheckedUncheckedColor(const QColor &c, const QColor &u);
    void         setDarkModeCheckedUncheckedColor(const QColor &c, const QColor &u);
    virtual void setColor(const QColor &color) override;

protected:
    QColor brightModeLeaveColor;
    QColor darkModeLeaveColor;
    QColor brightModeCheckedColor;
    QColor darkModeCheckedColor;

protected slots:
    virtual void setColorScheme(CellUiGlobal::COLOR_SCHEME mode) override;
};

#endif // CUSTOMPAGESWITCHBTN_H
