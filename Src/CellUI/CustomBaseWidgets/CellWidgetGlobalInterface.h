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

class CellWidgetGlobalInterface{
public:
    explicit CellWidgetGlobalInterface() = default;
    ~CellWidgetGlobalInterface() = default;

    inline const QColor color() const { return m_color; }
    virtual void        setColor(const QColor &color) = 0;
    void                setBrightDarkModeColor(const QColor& b, const QColor& d);

protected:
    CellUiGlobal::COLOR_SCHEME m_mode = CellUiGlobal::COLOR_SCHEME::_BRIGHT;
    QColor                     m_color;
    QColor                     brightmodeColor;
    QColor                     darkmodeColor;
    QPropertyAnimation        *animi;
    QPoint                     m_startPoint;
    QPoint                     m_windowPoint;
    bool                       m_move;

    virtual void setColorScheme(CellUiGlobal::COLOR_SCHEME mode) = 0;
};

#endif // CELLGLOBALWIDGET_H
