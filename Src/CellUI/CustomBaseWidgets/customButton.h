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
    enum Type:int{
        Static          = 0x01,
        Dynamic         = 0x02,
        Checkable       = 0x04,
        Radius          = 0x08,
        StaticRadius    = Static | Radius,
        DynamicRadius   = Dynamic | Radius,
        CheckableRadius = Checkable | Radius
    };
    Q_DECLARE_FLAGS(ButtonType, Type)

    explicit customButton(ButtonType type,QWidget *parent = nullptr);
    virtual ~customButton() = default;

    inline void
    setNaviBar() { naviVerBar = true; }

    //! Inheried from
    //! CellWidgetGlobalInterface.
    virtual void
    setColor(const QColor &color) override;

protected:
    //! Inherited from
    //! QPushButton.
    virtual void
    paintEvent(QPaintEvent *) override;

    virtual void
    changeToColor(const QColor& startColor, const QColor &targetColor, int duration) override;

    virtual void
    init() override;

    virtual void
    setEventConnections() override;

private:
    //! Core Color Switching Function
    //! For customButton.
    virtual void
    setAnimiStartEndColor(Cell::ColorScheme mode, QColor&, QColor&) override;

    ButtonType mType;
    bool naviVerBar = false;

public Q_SLOTS:
    virtual void
    setColorScheme(Cell::ColorScheme mode) override;

CheckablePublic:
    void
    setBrightCheckedColor(const CellVariant &color);

    void
    setDarkCheckedColor(const CellVariant &color);

CheckablePrivate:
    QColor *brightCheckedColor;
    QColor *darkCheckedColor;

DynamicPublic:
    void
    setBrightHoveringColor(const CellVariant &color);

    void
    setDarkHoveringColor(const CellVariant &color);

    inline void
    setAnimationDuration(int dur) { hoverAnimiDuration = dur; }

DynamicPrivate:
    virtual void
    enterEvent(QEvent*) override;

    virtual void
    leaveEvent(QEvent*) override;

    QColor  *brightHoveringColor;
    QColor  *darkHoveringColor;
    int      hoverAnimiDuration = 300;

StaticPublic:
    void
    setBrightHoverColor(const CellVariant &color);

    void
    setDarkHoverColor(const CellVariant &color);

StaticPrivate:
    QColor *brightHoverColor;
    QColor *darkHoverColor;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(customButton::ButtonType)

#endif // CUSTOMBUTTON_H
