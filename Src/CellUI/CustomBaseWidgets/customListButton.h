// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#ifndef CUSTOMLISTBUTTON_H
#define CUSTOMLISTBUTTON_H

#include "customButton.h"

class QHBoxLayout;
class customLabel;

class customListButton : public customButton{
friend class customButtonListWidget;
public:
    explicit customListButton(QWidget *parent = nullptr, const QString &text = "text");

    void   setMargins(int left = 0, int top = 0, int right = 0, int buttom = 0);
    void   setText(QString &text);

private:
    QHBoxLayout *mainLayout;
    customLabel *tag;

protected:
    void         init();
    virtual void setFont(const QFont &font);

protected Q_SLOTS:
    virtual void setColorScheme(CellUiGlobal::COLOR_SCHEME mode) override;
};

#endif // CUSTOMLISTBUTTON_H
