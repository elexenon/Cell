// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customOptionBlock.h"
#include "../../CellCore/Kits/CellUtility.h"
#include "../../CellCore/Kits/StyleSheetLoader.hpp"
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
    mainBlock->setBrightDarkModeColor(CellUiConst::GRAYLEVEL218, CellUiConst::GRAYLEVEL45);
    mainBlock->setLayout(mainBlockLayout);

    mainLayout->addWidget(mainBlock);
    setLayout(mainLayout);
}

void customOptionBlock::addThemeTag(const QString &name)
{
    theme = new customLabel(this);
    theme->setBrightDarkModeColor(CellUiConst::GRAYLEVEL70, CellUiConst::GRAYLEVEL255);
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

void customOptionBlock::setMainBlockBrightDarkModeColor(const QColor &b, const QColor &d)
{
    mainBlock->setBrightDarkModeColor(b, d);
}

void customOptionBlock::tidyItemTags()
{
    for(auto & item : *itemsList)
        item->setMargin(customOptionBlockItem::_LEFT, (itemTagMaxLen-item->tagLen)*17);
}
