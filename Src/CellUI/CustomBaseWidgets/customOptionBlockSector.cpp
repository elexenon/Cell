// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customOptionBlockSector.h"
#include "customOptionBlockItem.h"

#include <QVBoxLayout>

customOptionBlockSector::customOptionBlockSector(QWidget *parent):
    QWidget(parent),
    mainLayout(new QVBoxLayout),
    itemsList(new QList<customOptionBlockItem*>)
{
    setStyleSheet(CHAR2STR("background-color:transparent"));

    mainLayout->setMargin(0);
    mainLayout->addStretch();

    setLayout(mainLayout);
}

void customOptionBlockSector::addItem(customOptionBlockItem *item)
{
    if(item->getTagLen() > itemTagMaxLen) itemTagMaxLen = item->getTagLen();
    mainLayout->addWidget(item);
    mainLayout->addStretch();
    itemsList->append(item);
    item->setParent(this);
    setFixedHeight((itemsList->length()+1) * 35);
}

void customOptionBlockSector::setMargins(int left, int top, int right, int bottom)
{
    mainLayout->setContentsMargins(left,top,right,bottom);
}

void customOptionBlockSector::setColorScheme(CellUiGlobal::COLOR_SCHEME mode)
{
    for(auto & e : *itemsList)
        e->setColorScheme(mode);
}
