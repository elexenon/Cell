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

class QPropertyAnimation;
class QEasingCurve;
class CellVariant;

class CellWidgetGlobalInterface{
public:
    explicit CellWidgetGlobalInterface() = default;
    virtual ~CellWidgetGlobalInterface() = default;

    //! Return A Copy Of Current
    //! Color.
    inline const QColor
    color() const { return m_color; }
    //! Set The Duration Of Animation Of
    //! Virtual Function "changeToColor".
    inline void
    setColorAnimiDuration(int value) { this->colorSchemeAnimiDuration = value; }
    //! Return bright mode color
    //! by const reference.
    inline const QColor&
    brightModeColor() { return brightmodeColor; }
    //! Return dark mode color
    //! by const reference.
    inline const QColor&
    darkModeColor()   { return darkmodeColor; }
    //! Set bright/dark mode colors, so that cell
    //! will switch colors automatically.
    void          setBrightDarkModeColor(const CellVariant &b, const CellVariant &d);
    //! Inherited subclasses must implement this function
    //! to set unique color switching effects.
    virtual void  setColorScheme(Cell::ColorScheme mode) = 0;

protected:
    Cell::ColorScheme m_mode = Cell::ColorScheme::Bright;
    int                        colorSchemeAnimiDuration = static_cast<int>(Cell::AnimiDuration::GlobalDuration);
    QEasingCurve               easingCurve = QEasingCurve::InOutCubic;
    QColor                     m_color;
    QColor                     brightmodeColor;
    QColor                     darkmodeColor;
    QString                    BASEQSS;
    QPropertyAnimation        *animi;

    inline
    void         setColorEasingCurve(QEasingCurve curve) { this->easingCurve = curve; }
    virtual void setBaseQss(const QString& qss) = 0;
    virtual void changeToColor(const QColor& startColor, const QColor& targetColor, int duration) = 0;
    virtual void setColor(const QColor &color) = 0;
    virtual void setEventConnections();

    QList<CellWidgetGlobalInterface*> _modules;
};

#endif // CELLGLOBALWIDGET_H
