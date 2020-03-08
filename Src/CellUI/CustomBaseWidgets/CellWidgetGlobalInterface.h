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
    //! Set The Duration Of Animation Of
    //! Virtual Function "changeToColor".
    inline void
    setSwitchDuration(int value) { this->switchDuration = value; }
    //! Return bright mode color
    //! by const reference.
    inline const QColor&
    brightColor() { return brightmodeColor; }
    //! Return dark mode color
    //! by const reference.
    inline const QColor&
    darkModeColor()   { return darkmodeColor; }
    //! Set bright/dark mode colors, so that cell
    //! will switch colors automatically.
    void
    setBrightDarkColor(const CellVariant &b, const CellVariant &d);
    //! Inherited subclasses can reimplement this function
    //! to set unique color switching effects.
    virtual void
    setColorScheme(Cell::ColorScheme mode);

protected:
    Cell::ColorScheme mMode         = Cell::ColorScheme::Bright;
    int                               switchDuration = static_cast<int>(Cell::AnimiDuration::GlobalDuration);
    QEasingCurve                      easingCurve = QEasingCurve::InOutCubic;
    QColor                            mColor;
    QColor                            brightmodeColor;
    QColor                            darkmodeColor;
    QPropertyAnimation                animi;
    QPropertyAnimation               *animiPtr;
    QList<CellWidgetGlobalInterface*> _modules;

    inline void
    setColorEasingCurve(QEasingCurve curve) { this->easingCurve = curve; }

    virtual void
    setAnimiStartEndColor(Cell::ColorScheme mode, QColor &startColor, QColor &endColor);

    virtual void
    init() = 0;

    virtual void
    changeToColor(const QColor& startColor, const QColor& targetColor, int duration) = 0;

    virtual void
    setColor(const QColor &color) = 0;

    virtual void
    setEventConnections() = 0;
};

#endif // CELLGLOBALWIDGET_H
