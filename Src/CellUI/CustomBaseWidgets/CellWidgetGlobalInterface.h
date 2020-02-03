// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef CELLGLOBALWIDGET_H
#define CELLGLOBALWIDGET_H

#include "../../CellCore/Kits/CellUtility.h"
#include <QWidget>

class QPropertyAnimation;
class QEasingCurve;

class CellWidgetGlobalInterface{
public:
    explicit CellWidgetGlobalInterface() = default;
    virtual ~CellWidgetGlobalInterface() = default;

    inline const QColor color() const { return m_color; }
    inline void         setColorAnimiDuration(int value) { this->colorChangeAnimiDuration = value; }
    inline void         setColorEasingCurve(QEasingCurve curve) { this->easingCurve = curve; }
    virtual void        setColor(const QColor &color) = 0;
    virtual void        setBaseQss(const QString& qss) = 0;
    virtual void        changeToColor(const QColor& startColor, const QColor& targetColor) = 0;
    void                setBrightDarkModeColor(const QColor& b, const QColor& d);

protected:
    CellUiGlobal::COLOR_SCHEME m_mode = CellUiGlobal::COLOR_SCHEME::_BRIGHT;
    int                        colorChangeAnimiDuration = CellUiGlobal::CELL_GLOBALANIMIDURATION;
    QEasingCurve               easingCurve = QEasingCurve::InOutCubic;
    QColor                     m_color;
    QColor                     brightmodeColor;
    QColor                     darkmodeColor;
    QString                    BASEQSS;
    QPropertyAnimation        *animi;

    virtual void setColorScheme(CellUiGlobal::COLOR_SCHEME mode) = 0;
};

#endif // CELLGLOBALWIDGET_H
