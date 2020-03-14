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
    Q_PROPERTY(qreal focusEdgeOffset READ focusEdgeOffset WRITE setFocusEdgeOffset)
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
    //! Register Enum Type "Type"
    //! Into QFlags.
    Q_DECLARE_FLAGS(ButtonType, Type)

    explicit customButton(ButtonType type,QWidget *parent = nullptr);
    virtual ~customButton();
    //! Inheried from
    //! CellWidgetGlobalInterface.
    virtual void
    setColor(const QColor &color) override;

protected:
    //! Inherited from
    //! QPushButton.
    virtual void
    paintEvent(QPaintEvent *) override;
    //! Inheried from
    //! CellWidgetGlobalInterface.
    virtual void
    changeToColor(const QColor& startColor, const QColor &targetColor, int duration) override;
    //! Inheried from
    //! CellWidgetGlobalInterface.
    virtual void
    init() override;
    //! Inheried from
    //! CellWidgetGlobalInterface.
    virtual void
    setEventConnections() override;

private:
    //! Inheried from
    //! CellWidgetGlobalInterface.
    //! Core Color Switching Function
    //! For customButton.
    virtual void
    setAnimiStartEndColor(Cell::ColorScheme mode, QColor&, QColor&) override;

    ButtonType mType;

public Q_SLOTS:
    //! Inheried from
    //! CellWidgetGlobalInterface.
    inline virtual void
    setColorScheme(Cell::ColorScheme mode) override { CellWidgetGlobalInterface::setColorScheme(mode); }

CheckablePublic:
    //! Set The Bright Color
    //! Of State "Checked".
    void
    setBrightCheckedColor(const CellVariant &color);
    //! Set The Dark Color
    //! Of State "Checked".
    void
    setDarkCheckedColor(const CellVariant &color);
    //! If This Function Is Called,
    //! And The State Of Button Is
    //! "Checkable", Then There's
    //! Going To Be A Vertical Thin
    //! Blue Bar Right On The Button's
    //! Edge.
    inline void
    drawMarkOnChecked() { mDrawMark = true; }
    //! If This Function Is Called,
    //! And The State Of Button Is
    //! "Checkable", Then There's
    //! Going To Be A Blue Edge All
    //! Around The Button That Stands
    //! For "Focus".
    inline void
    drawFocusEdgeOnChecked() { mDrawFocusEdge = true; }
    //! If mDrawFocusEdge Is True, T-
    //! his Function Will Update Focus
    //! Edge.
    void
    updateFocusEdge();
    inline qreal
    focusEdgeOffset() const { return mFocusEdgeOffset; }
    inline void
    setFocusEdgeOffset(const qreal offset) { mFocusEdgeOffset = offset; update(); }

CheckablePrivate:
    QColor *brightCheckedColor;
    QColor *darkCheckedColor;
    bool  mDrawMark;
    bool  mDrawFocusEdge;
    //! 0.0 ~ 10.0
    qreal mFocusEdgeOffset = 10.0;

DynamicPublic:
    //! Set The Bright Color
    //! Of State "Mouse Hovering".
    void
    setBrightHoveringColor(const CellVariant &color);
    //! Set The Dark Color
    //! Of State "Mouse Hovering".
    void
    setDarkHoveringColor(const CellVariant &color);
    //! Set The Switching
    //! Animation Duration.
    inline void
    setAnimationDuration(int dur) { hoverAnimiDuration = dur; }

DynamicPrivate:
    //! Inheried from
    //! QPushButton.
    virtual void
    enterEvent(QEvent*) override;
    //! Inheried from
    //! QPushButton.
    virtual void
    leaveEvent(QEvent*) override;

    QColor  *brightHoveringColor;
    QColor  *darkHoveringColor;
    int      hoverAnimiDuration = 300;

StaticPublic:
    //! Set The Bright Color
    //! Of State "Mouse Hovering".
    void
    setBrightHoverColor(const CellVariant &color);
    //! Set The Dark Color
    //! Of State "Mouse Hovering".
    void
    setDarkHoverColor(const CellVariant &color);

StaticPrivate:
    QColor *brightHoverColor;
    QColor *darkHoverColor;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(customButton::ButtonType)

#endif // CUSTOMBUTTON_H
