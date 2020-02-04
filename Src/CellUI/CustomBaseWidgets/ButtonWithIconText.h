// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef BUTTONWITHICONTEXT_H
#define BUTTONWITHICONTEXT_H

#include "customButton.h"

class QLabel;
class customLabel;
class QHBoxLayout;

class ButtonWithIconText : public customButton{
    Q_OBJECT
public:
    explicit ButtonWithIconText(TYPE type = STATIC, QWidget *parent = nullptr);
    virtual ~ButtonWithIconText() override = default;

    void Init(const QString &filePath, int iconWidth, int iconHeight, const QString& text = "Button", int fontSize = 18);

protected:
    QHBoxLayout *mainLayout;
    QLabel      *icon;
    customLabel *tag;
};

#endif // BUTTONWITHICONTEXT_H
