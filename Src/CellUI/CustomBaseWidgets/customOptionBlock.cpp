// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "customOptionBlock.h"
#include "../../CellCore/CellNamespace.h"
#include "../../CellCore/Kits/CellUtility.h"
#include "customOptionBlockItem.h"
#include "customLabel.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

customOptionBlock::customOptionBlock(QWidget *parent, const QString& name):
    customFrame(customFrame::_REGULAR, parent),
    mainLayout(new QVBoxLayout),
    mainBlockLayout(new QVBoxLayout),
    itemsList(new QList<customOptionBlockItem*>)
{
    setStyleSheet(CHAR2STR("background-color:transparent"));

    mainLayout->setMargin(0);
    mainLayout->setSpacing(3);
    mainBlockLayout->setMargin(0);
    mainBlockLayout->setSpacing(0);

    if(name != " ") addThemeTag(name);

    mainBlock = new customFrame(customFrame::_RADIUS, this);
    mainBlock->setBrightDarkModeColor(Cell::CGL218, Cell::CGL45);
    mainBlock->setLayout(mainBlockLayout);

    mainLayout->addWidget(mainBlock);
    setLayout(mainLayout);
}

void customOptionBlock::addThemeTag(const QString &name)
{
    theme = new customLabel(this);
    theme->setBrightDarkModeColor(Cell::CGL70, Cell::CGL255);
    CellUiGlobal::setCustomTextLabel(theme, CHAR2STR("Microsoft YaHei UI Light"), 15, name);

    QHBoxLayout *themeTagLayout = new QHBoxLayout;
    themeTagLayout->addWidget(theme);
    themeTagLayout->addStretch();
    themeTagLayout->setMargin(0);

    mainLayout->addLayout(themeTagLayout);
}

void customOptionBlock::addItem(customOptionBlockItem *item, bool addSplitterLine)
{
    if(item->tagLen > itemTagMaxLen) itemTagMaxLen = item->tagLen;

    itemsList->append(item);
    mainBlockLayout->addWidget(item);
    item->setParent(mainBlock);

    blockHeight += item->height();
    setFixedHeight(blockHeight + 25);

    if(addSplitterLine){
        QFrame *lineSplitter = CellUiGlobal::getLine(CellUiGlobal::LINE_TYPE::HLine);
        QHBoxLayout *layout = new QHBoxLayout;
        layout->setContentsMargins(10, 0, 10, 0);
        layout->addWidget(lineSplitter);
        mainBlockLayout->addLayout(layout);
        blockHeight += 1;
        setFixedHeight(blockHeight + 25);
    }
}

void customOptionBlock::setMainBlockBrightDarkModeColor(const CellVariant b, const CellVariant d)
{
    mainBlock->setBrightDarkModeColor(b, d);
}

void customOptionBlock::_tidyItems(int value)
{
    for(auto & item : *itemsList)
        if(value == -1)
            item->setMargin(customOptionBlockItem::_LEFT, (itemTagMaxLen-item->tagLen)*customOptionBlockItem::TagTextSize);
        else
            item->setMargin(customOptionBlockItem::_LEFT, (value-item->tagLen)*customOptionBlockItem::TagTextSize);
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
