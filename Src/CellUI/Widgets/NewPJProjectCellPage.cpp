// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "NewPJProjectCellPage.h"

#include <QComboBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QFileDialog>

NewPJProjectCellPage::NewPJProjectCellPage(QWidget *parent):
    newPJPageBase(parent)
{
    init();
    setEventConnections();
}

void NewPJProjectCellPage::init()
{
    newPJPageBase::setPageTitle(CHAR2STR("连接到Cell运算库。"));
    newPJPageBase::enableToolChainsBlock();
}

void NewPJProjectCellPage::setEventConnections()
{
}
