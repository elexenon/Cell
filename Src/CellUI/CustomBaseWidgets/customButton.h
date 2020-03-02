// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>

#include "CellWidgetGlobalInterface.h"
#include "../../CellCore/Kits/CellGlobalMacros.h"

class customButton : public QPushButton, implements CellWidgetGlobalInterface{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
public:
    enum Type{
        Static,       Dynamic,       Checkable,
        StaticRadius, DynamicRadius, CheckableRadius
    };
    explicit customButton(Type type = Static,QWidget *parent = nullptr);
    virtual ~customButton() = default;

protected:
    virtual void setColor(const QColor &color) override;
    virtual void setBaseQss(const QString &qss) override;
    virtual void changeToColor(const QColor& startColor, const QColor &targetColor, int duration) override;

private:
    void setAnimiStartEndColor(Cell::ColorScheme mode, QColor&, QColor&);
    Type mType;

public Q_SLOTS:
    virtual void setColorScheme(Cell::ColorScheme mode) override;

CheckablePublic:
    void setBrightModeCheckedColor(const CellVariant &color);
    void setDarkModeCheckedColor(const CellVariant &color);
CheckableProtected:
    QColor brightModeCheckedColor;
    QColor darkModeCheckedColor;

DynamicPublic:
    void setBrightModeHoveringColor(const CellVariant &color);
    void setDarkModeHoveringColor(const CellVariant &color);
    inline
    void setAnimationDuration(int dur) { hoverAnimiDuration = dur; }
DynamicProtected:
    virtual void enterEvent(QEvent*) override;
    virtual void leaveEvent(QEvent*) override;
    QColor  brightModeHoveringColor;
    QColor  darkModeHoveringColor;
    int     hoverAnimiDuration = 300;

StaticPublic:
    void setBrightModeHoverColor(const CellVariant &color);
    void setDarkModeHoverColor(const CellVariant &color);
StaticProtected:
    QColor brightModeHoverColor;
    QColor darkModeHoverColor;
};

#endif // CUSTOMBUTTON_H
