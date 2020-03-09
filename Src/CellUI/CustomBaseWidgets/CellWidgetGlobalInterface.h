// This class decalars necesssary data members and abstract interfaces
// to for Cell's function of global color switching.A derived class mu-
// st inherit from this class in order to implement color transform.
//
// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#ifndef CELLGLOBALWIDGET_H
#define CELLGLOBALWIDGET_H

#include "../../CellCore/CellNamespace.h"
#include "../../CellCore/CellVariant.h"
#include <QWidget>

class CellWidgetGlobalInterface{
public:
    explicit CellWidgetGlobalInterface() = default;
    virtual ~CellWidgetGlobalInterface() = default;
    //! Return A Copy Of Current
    //! Color.
    inline const QColor
    color() const { return mColor; }
    //! Return bright mode color
    //! by const reference.
    inline const QColor&
    brightColor() { return brightmodeColor; }
    //! Return dark mode color
    //! by const reference.
    inline const QColor&
    darkColor()   { return darkmodeColor; }
    //! Set bright/dark mode colors, so that cell
    //! will switch colors automatically.
    void
    setBrightDarkColor(const CellVariant &b, const CellVariant &d);
    //! Inherited subclasses can reimplement this function
    //! to set unique color switching effects.
    virtual void
    setColorScheme(Cell::ColorScheme mode);

protected:
    QList<CellWidgetGlobalInterface*> _modules;
    QColor                            mColor;
    QColor                            brightmodeColor;
    QColor                            darkmodeColor;
    QPropertyAnimation                animi;
    QPropertyAnimation               *animiPtr;

    static Cell::ColorScheme mMode;
    static QEasingCurve      easingCurve;
    static Cell::SwitchMode  switchMode;
    static int               switchDuration;
    static bool              autoSwitch;

    //! Set The Duration Of Animation Of
    //! Virtual Function "changeToColor".
    inline static void
    setSwitchDuration(int value) { CellWidgetGlobalInterface::switchDuration = value; }
    //! Set Easing Curve Of Animation Of
    //! Virtual Function "changeToColor".
    inline static void
    setColorEasingCurve(QEasingCurve curve) { CellWidgetGlobalInterface::easingCurve = curve; }
    //! This Function Controls The Behavior Of
    //! Choosing Of StartColor and
    //! EndColor Of Subclasses.
    virtual void
    setAnimiStartEndColor(Cell::ColorScheme mode, QColor &startColor, QColor &endColor);
    //! Force Subclasses To Implement
    //! Initializing Processes.
    virtual void
    init() = 0;
    //! This Is A Polymorphic Behavior.
    //! How The Switching Effect Works
    //! Depends On The Implementations
    //! Of Subclasses.
    virtual void
    changeToColor(const QColor& startColor, const QColor& targetColor, int duration) = 0;
    //! This Is A Polymorphic Behavior.
    //! It Resolves How Subclasses Set
    //! "mColor"
    virtual void
    setColor(const QColor &color) = 0;
    //! Force Subclasses To Implement
    //! Events Connecting Processes.
    virtual void
    setEventConnections() = 0;
};

#endif // CELLGLOBALWIDGET_H
