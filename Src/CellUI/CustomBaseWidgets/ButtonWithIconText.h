// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#ifndef BUTTONWITHICONTEXT_H
#define BUTTONWITHICONTEXT_H

#include "customButton.h"

class QLabel;
class customLabel;
class QHBoxLayout;

class ButtonWithIconText : public customButton{
    Q_OBJECT
public:
    explicit ButtonWithIconText(customButton::Type type = Static, QWidget *parent = nullptr);

    void init(const QString &filePath, int iconWidth, int iconHeight, const QString& text = "Button", int fontSize = 18);

protected:
    QHBoxLayout *mainLayout;
    QLabel      *icon;
    customLabel *tag;
};

#endif // BUTTONWITHICONTEXT_H
