// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#ifndef CUSTOMSWITCH_H
#define CUSTOMSWITCH_H

#include <QWidget>

#include "../CustomBaseWidgets/CellWidgetGlobalInterface.h"

class QPropertyAnimation;

class customSwitch : public QWidget{
    Q_OBJECT
    Q_PROPERTY(qreal triggerOffset READ triggerOffset WRITE setTriggerOffset)
public:
    explicit customSwitch(QWidget *parent = nullptr);
    ~customSwitch() = default;

    void setChecked(bool checked);
    inline
    void setMargin(qreal value) { margin = value; update(); }

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void  init();
    void  switchTrigger();
    inline
    void  setTriggerOffset(qreal value) { triggerPosOffset = value; update();}
    inline
    qreal triggerOffset() { return triggerPosOffset; }

    bool   isChecked = false;
    qreal  triggerPosOffset = 0.0;
    qreal  triggerDiam = 23;
    QColor triggerColor;
    QColor paddingColor;
    qreal  paddingRadius = 8;
    qreal  margin = 3;

    QPropertyAnimation animi;

signals:
    void clicked(bool checked);
};

#endif // CUSTOMSWITCH_H
