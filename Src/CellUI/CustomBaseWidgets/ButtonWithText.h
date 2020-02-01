// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef BUTTONWITHTEXT_H
#define BUTTONWITHTEXT_H

#include "customButton.h"

class customLabel;
class QVBoxLayout;

class ButtonWithText : public customButton{
    Q_OBJECT
public:
    explicit ButtonWithText(TYPE type = STATIC,QWidget *parent = nullptr);
    virtual ~ButtonWithText() override = default;

    void Init(const QString& text = "Button", int fontSize = 18) ;

protected:
    QVBoxLayout *mainLayout;
    customLabel *tag;
};

#endif // BUTTOMWITHTEXT_H
