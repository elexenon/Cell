// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
//
// This class implemented dropshadow effect & "color" custom property.
#ifndef DROPSHADOWDIALOG_H
#define DROPSHADOWDIALOG_H

#include <QDialog>

#include "CellWidgetGlobalInterface.h"
#include "../../CellCore/Kits/CellGlobalMacros.h"

class customWinstyleDialog : public QDialog, implements CellWidgetGlobalInterface
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
public:
    explicit customWinstyleDialog(QWidget *parent = nullptr);
    virtual ~customWinstyleDialog() = default;

    virtual void setColor(const QColor &color) override;
    virtual void setBaseQss(const QString &qss) override;
    virtual void changeToColor(const QColor &startColor, const QColor &targetColor, int duration) override;

protected:
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    void         LoadWinStyle(QWidget *obj);

    QPoint m_startPoint;
    QPoint m_windowPoint;
    bool   m_move; 

protected Q_SLOTS:
    virtual void setColorScheme(Cell::ColorScheme mode) override;
};


#endif // DROPSHADOWDIALOG_H
