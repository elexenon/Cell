// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "customOptionBlock.h"
#include "customOptionBlockItem.h"
#include "../../CellCore/CellNamespace.h"
#include "../../CellCore/Kits/CellUtility.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

customOptionBlock::customOptionBlock(const QString& name, QWidget *parent):
    optionBlockBase(name, parent),
    mainBlockLayout(new QVBoxLayout),
    itemsList(new QList<customOptionBlockItem*>)
{
    init();
}

void customOptionBlock::init()
{
    mainBlockLayout->setMargin(0);
    mainBlockLayout->setSpacing(0);
    mainBlock = new customFrame(customFrame::Type::Radius, this);
    mainBlock->setBrightDarkColor(Cell::CGL218, Cell::CGL70);
    mainBlock->setLayout(mainBlockLayout);

    mainLayout->addWidget(mainBlock);
    setMinimumHeight(50);

    CellWidgetGlobalInterface::_modules << mainBlock;
}

void customOptionBlock::addItem(customOptionBlockItem *item, bool addSplitterLine)
{
    if(item->tagLen > itemTagMaxLen) itemTagMaxLen = item->tagLen;

    itemsList->append(item);
    mainBlockLayout->addWidget(item);
    item->setParent(mainBlock);

    _addSplitterLine(addSplitterLine);

    CellWidgetGlobalInterface::_modules << item;
}

void customOptionBlock::addItem(QWidget *optionWidget, const QString &tag, const QString &hint, bool addSplitterLine)
{
    auto *item = new customOptionBlockItem(mainBlock, tag);
    item->setOptionWidget(optionWidget);
    if(hint != CMPSTR("")) item->setHint(hint);

    if(item->tagLen > itemTagMaxLen) itemTagMaxLen = item->tagLen;

    itemsList->append(item);
    mainBlockLayout->addWidget(item);

    _addSplitterLine(addSplitterLine);

    CellWidgetGlobalInterface::_modules << item;
}

void customOptionBlock::setMainBlockBrightDarkModeColor(const CellVariant &b, const CellVariant &d)
{
    mainBlock->setBrightDarkColor(b, d);
}

void customOptionBlock::_tidyItems(int value)
{
    for(auto & item : *itemsList)
        if(value == -1)
            item->setMargin(customOptionBlockItem::Left, (itemTagMaxLen-item->tagLen)*customOptionBlockItem::TagTextSize);
        else
            item->setMargin(customOptionBlockItem::Left, (value-item->tagLen)*customOptionBlockItem::TagTextSize);
}

void customOptionBlock::_addSplitterLine(bool add)
{
    if(!add) return;
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(10, 0, 10, 0);
    layout->addWidget(CellUiGlobal::getLine(Cell::LineType::HLine));
    mainBlockLayout->addLayout(layout);
}

void customOptionBlock::tidyItems(customOptionBlock *another)
{
    if(another == nullptr){
        _tidyItems();
    }else{
        int anothMax = another->getItemTagMaxLen();
        if(itemTagMaxLen < anothMax){
            _tidyItems(anothMax);
            another->_tidyItems(anothMax);
        }
        else{
            another->_tidyItems(itemTagMaxLen);
            _tidyItems(itemTagMaxLen);
        }
    }
}
