// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef CELLWINSTYLEINTERFACE_H
#define CELLWINSTYLEINTERFACE_H

#include <QWidget>

#include "CellWidgetGlobalInterface.h"
#include "../../CellCore/Kits/CustomCppInterfaceDefination.h"

class customWinstyleWidget : public QWidget, implements CellWidgetGlobalInterface{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
public:
    explicit     customWinstyleWidget(QWidget *parent = nullptr);
    virtual void setColor(const QColor &color) override;
protected:
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    void         LoadWinStyle(QWidget *obj);  

protected slots:
    virtual void setColorScheme(CellUiGlobal::COLOR_SCHEME mode) override;
};
#endif // CELLWINSTYLEINTERFACE_H
