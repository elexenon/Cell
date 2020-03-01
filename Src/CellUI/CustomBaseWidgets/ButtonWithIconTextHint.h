// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
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

    void init(const QString &fileName, int iconWidth, int iconHeight,
              const QString& text = "Button", int fontSize = 23, const QString& hint = "hint");

protected:
    QHBoxLayout *mainLayout;
    QLabel      *icon;
    customLabel *tag;
    customLabel *hint;
};

#endif // BUTTONWITHICONTEXTHINT_H
