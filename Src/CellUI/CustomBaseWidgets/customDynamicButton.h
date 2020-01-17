// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef CUSTOMDYNAMICBUTTON_H
#define CUSTOMDYNAMICBUTTON_H

#include "customStaticButton.h"

class customDynamicButton : public customStaticButton{
    Q_OBJECT
    const QString BASEQSS;
public:
    explicit customDynamicButton(QWidget *parent = nullptr);
    ~customDynamicButton() override = default;

    void         setBrightModeEnterLeaveColor(const QColor &e,const QColor &l);
    void         setDarkModeEnterLeaveColor(const QColor &e,const QColor &l);

    inline void  setAnimationDuration(int dur) { animiDuration = dur; }
    virtual void setColor(const QColor &color) override;

protected:
    virtual void enterEvent(QEvent*) override;
    virtual void leaveEvent(QEvent*) override;

private:
    QColor brightModeEnterColor;
    QColor darkModeEnterColor;
    int    animiDuration;
};

#endif // CUSTOMDYNAMICBUTTON_H
