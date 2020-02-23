// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#ifndef CUSTOMFRAME_H
#define CUSTOMFRAME_H

#include <QFrame>
#include "CellWidgetGlobalInterface.h"
#include "../../CellCore/Kits/CellGlobalMacros.h"

class customFrame : public QFrame, implements CellWidgetGlobalInterface
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
public:
    enum CUSTOMFRAME_TYPE{
        _REGULAR, _RADIUS
    };
    explicit customFrame(CUSTOMFRAME_TYPE type, QWidget *parent = nullptr);
    virtual ~customFrame() override = default;

protected:
    virtual void setBaseQss(const QString& qss) override;
    virtual void setColor(const QColor &color) override;
    virtual void changeToColor(const QColor& startColor, const QColor &targetColor, int duration) override;
    virtual void setEventConnections() override;

private:
    CUSTOMFRAME_TYPE m_type;

public Q_SLOTS:
    virtual void setColorScheme(CellUiGlobal::COLOR_SCHEME mode) override;
};
#endif
