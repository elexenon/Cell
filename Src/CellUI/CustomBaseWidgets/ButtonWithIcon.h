// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef BUTTONWITHICON_H
#define BUTTONWITHICON_H

#include "customButton.h"

class QLabel;
class QHBoxLayout;

class ButtonWithIcon : public customButton{
    Q_OBJECT
public:
    explicit ButtonWithIcon(TYPE type = STATIC,QWidget *parent = nullptr);
    virtual ~ButtonWithIcon() override = default;

    void Init(const QString& fileName, int iconWidth, int iconHeight);

protected:
    QHBoxLayout *mainLayout;
    QLabel *icon;
};

#endif // BUTTONWITHICON_H
