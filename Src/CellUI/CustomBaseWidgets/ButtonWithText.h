// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
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

    void init(const QString& text = "Button", int fontSize = 18);
    void setTextColor(const CellVariant &b, const CellVariant &d);

protected:
    QVBoxLayout *mainLayout;
    customLabel *tag;
};

#endif // BUTTOMWITHTEXT_H
