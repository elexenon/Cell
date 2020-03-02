// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#ifndef CELLGLOBALWIDGET_H
#define CELLGLOBALWIDGET_H

#include "../../CellCore/Kits/CellUtility.h" // ColorScheme & CELL_GLOBALANIMATION
#include "../../CellCore/CellVariant.h"
#include <QWidget>

class QPropertyAnimation;
class QEasingCurve;
class CellVariant;

class CellWidgetGlobalInterface{
public:
    explicit CellWidgetGlobalInterface() = default;
    virtual ~CellWidgetGlobalInterface() = default;

    inline
    const QColor color() const { return m_color; }
    inline
    void         setColorAnimiDuration(int value) { this->colorSchemeAnimiDuration = value; }
    void         setBrightDarkModeColor(const CellVariant &b, const CellVariant &d);

protected:
    Cell::ColorScheme m_mode = Cell::ColorScheme::_BRIGHT;
    int                        colorSchemeAnimiDuration = static_cast<int>(Cell::GlobalDuration);
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
    virtual void setColorScheme(Cell::ColorScheme mode) = 0;
    virtual void setEventConnections();
};

#endif // CELLGLOBALWIDGET_H
