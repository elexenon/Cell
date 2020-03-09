// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "NewPJPredictEarPage.h"

NewPJPredictEarPage::NewPJPredictEarPage(QWidget *parent):
    newPJPageBase(parent)
{
    init();
    setEventConnections();
}

void NewPJPredictEarPage::init()
{
    newPJPageBase::setPageTitle(CHAR2STR("基于Cell运算库的地震预测。"));
    newPJPageBase::enableToolChainsBlock();
}

void NewPJPredictEarPage::setEventConnections()
{

}
