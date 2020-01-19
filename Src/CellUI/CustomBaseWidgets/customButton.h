// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>

#include "CellWidgetGlobalInterface.h"
#include "../../CellCore/Kits/CellGlobalMacros.h"

class customButton : public QPushButton, implements CellWidgetGlobalInterface{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
    QString BASEQSS;
public:
    enum TYPE{
        STATIC,
        DYNAMIC,
        CHECKABLE
    };
    explicit customButton(TYPE type = STATIC,QWidget *parent = nullptr);
    ~customButton() override = default;
    virtual void setColor(const QColor &color) override;

private:
    void setAnimiStartEndColor(CellUiGlobal::COLOR_SCHEME mode, QColor&, QColor&);
    TYPE type;

protected slots:
    virtual void setColorScheme(CellUiGlobal::COLOR_SCHEME mode) override;

Checkable_Public:
    inline
    void setBrightModeCheckedColor(const QColor &color) { brightModeCheckedColor = color; }
    inline
    void setDarkModeCheckedColor(const QColor &color)   { darkModeCheckedColor = color; }
Checkable_Protected:
    QColor brightModeCheckedColor;
    QColor darkModeCheckedColor;

Dynamic_Public:
    inline
    void setBrightModeHoveringColor(const QColor &color) { brightModeHoveringColor = color; }
    inline
    void setDarkModeHoveringColor(const QColor &color)   { darkModeHoveringColor = color; }
    inline
    void setAnimationDuration(int dur) { animiDuration = dur; }
Dynamic_Protected:
    virtual void enterEvent(QEvent*) override;
    virtual void leaveEvent(QEvent*) override;
    QColor       brightModeHoveringColor;
    QColor       darkModeHoveringColor;
    int          animiDuration;

Static_Public:
    inline
    void setBrightModeHoverColor(const QColor& color) { brightModeHoverColor = color; }
    inline
    void setDarkModeHoverColor(const QColor& color)   { darkModeHoverColor = color; }
Static_Protected:
    QColor brightModeHoverColor;
    QColor darkModeHoverColor;
};

#endif // CUSTOMBUTTON_H
