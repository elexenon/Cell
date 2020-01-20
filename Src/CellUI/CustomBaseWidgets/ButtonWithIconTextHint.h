// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef BUTTONWITHICONTEXTHINT_H
#define BUTTONWITHICONTEXTHINT_H

#include "customButton.h"

class customLabel;
class QHBoxLayout;
class QLabel;

class ButtonWithIconTextHint : public customButton{
    Q_OBJECT
public:
    explicit ButtonWithIconTextHint(TYPE type = STATIC,QWidget *parent = nullptr);
    virtual ~ButtonWithIconTextHint() override = default;

    void Init(const QString &fileName, int iconWidth, int iconHeight,
              const QString& text = "Button", int fontSize = 23, const QString& hint = "hint");

protected:
    QHBoxLayout *mainLayout;
    QLabel      *icon;
    customLabel *tag;
    customLabel *hint;
};

#endif // BUTTONWITHICONTEXTHINT_H
