// Copyright 2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef CUSTOMDYNAMICBUTTON_H
#define CUSTOMDYNAMICBUTTON_H

#include <QPushButton>
#include "cell_util.h"
#include "customStaticButton.h"

class customDynamicButton : public customStaticButton{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

    const QString BASEQSS;

public:
    explicit customDynamicButton(QWidget *parent = nullptr);
    ~customDynamicButton() override = default;

    const QColor        color() const;
    void                setColor(const QColor color);

    void                setBrightModeEnterLeaveColor(const QColor &e,const QColor &l);
    void                setDarkModeEnterLeaveColor(const QColor &e,const QColor &l);
    void                setAnimationDuration(int dur);
    void                Init();

protected:
    virtual void        enterEvent(QEvent*) override;
    virtual void        leaveEvent(QEvent*) override;

private:
    QColor              brightModeEnterColor;
    QColor              darkModeEnterColor;
    int                 animiDuration;

private slots:
    void                backToCurrColor();
};

#endif // CUSTOMDYNAMICBUTTON_H
