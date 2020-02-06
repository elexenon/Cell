// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef CUSTOMCOMBOBOX_H
#define CUSTOMCOMBOBOX_H

#include "customFrame.h"

class QHBoxLayout;
class customLabel;
class ButtonWithIcon;

class customDialogButton : public customFrame{
    Q_OBJECT
public:
    explicit customDialogButton(const QString& state, QWidget *parent = nullptr);
    inline
    const ButtonWithIcon* getTrigger() { return trigger;}

protected:
    customLabel                   *currState;
    ButtonWithIcon                *trigger;
    QHBoxLayout                   *mainLayout;

};

#endif // CUSTOMCOMBOBOX_H
