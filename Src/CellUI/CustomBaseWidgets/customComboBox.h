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
class customButton;
class customOptionBlock;

class customComboBox : public customFrame{
    Q_OBJECT
public:
    explicit customComboBox(const QString& state, QWidget *parent = nullptr);

protected:
    customLabel       *currState;
    customButton      *trigger;
    customOptionBlock *optionBlock;
    QHBoxLayout       *mainLayout;
};

#endif // CUSTOMCOMBOBOX_H
