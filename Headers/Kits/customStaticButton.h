// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef CUSTOMPAGESWITCHBTN_H
#define CUSTOMPAGESWITCHBTN_H

#include <QPushButton>
#include "cell_util.h" // COLOR_SCHEME

class customStaticButton : public QPushButton{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)

    const QString BASEQSS;
public:
    explicit customStaticButton(QWidget *parent = nullptr);
    ~customStaticButton() override = default;

    void         Init();
    void         setBrightModeCheckedUncheckedColor(const QColor &c, const QColor &u);
    void         setDarkModeCheckedUncheckedColor(const QColor &c, const QColor &u);

    const QColor color() const;
    void         setColor(const QColor &color);

protected:
    QPropertyAnimation      *animi;
    CellGlobal::COLOR_SCHEME m_colorScheme;

    QColor currColor;
    QColor brightModeLeaveColor;
    QColor darkModeLeaveColor;
    QColor brightModeCheckedColor;
    QColor darkModeCheckedColor;

protected slots:
    void setColorScheme(CellGlobal::COLOR_SCHEME mode);
};

#endif // CUSTOMPAGESWITCHBTN_H
