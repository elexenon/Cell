// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef NEWPJPROJECTPAGE_H
#define NEWPJPROJECTPAGE_H

#include "../CustomBaseWidgets/customFrame.h"

class customLabel;
class QComboBox;

class NewPJProjectCellPage : public customFrame{
    Q_OBJECT
public:
    explicit NewPJProjectCellPage(QWidget *parent = nullptr);
    ~NewPJProjectCellPage() override = default;

private:
    customLabel *label_title;

    customLabel *label_pjConfig;
    customFrame *optionBlock1;
    customLabel *label_pjName;
    QComboBox   *comboBox1;
    customLabel *label_pjLoc;
    QComboBox   *comboBox2;

    customLabel *label_kitConfig;
    customFrame *optionBlock2;
    customLabel *label_version;
    QComboBox   *comboBox3;
    customLabel *label_encode;
    QComboBox   *comboBox4;

private:
    void Init();
    void setEventConnections();
};

#endif // NEWPJPROJECTPAGE_H
