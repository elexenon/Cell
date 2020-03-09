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
    customFrame(customFrame::Type::Regular, parent),
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

    mainBlock = new customFrame(customFrame::Type::Radius, this);
    mainBlock->setBrightDarkColor(Cell::CGL218, Cell::CGL70);
    mainBlock->setLayout(mainBlockLayout);

    mainLayout->addWidget(mainBlock);
    setLayout(mainLayout);
    setMinimumHeight(50);

    _modules << mainBlock;
}

void customOptionBlock::addThemeTag(const QString &name)
{
    _theme = name;
    theme = new customLabel(this);
    theme->setBrightDarkColor(Cell::CGL70, Cell::CGL255);
    CellUiGlobal::setCustomTextLabel(theme, CHAR2STR("Microsoft YaHei UI Light"), 15, name);

    QHBoxLayout *themeTagLayout = new QHBoxLayout;
    themeTagLayout->addWidget(theme);
    themeTagLayout->addStretch();
    themeTagLayout->setMargin(0);

    mainLayout->addLayout(themeTagLayout);

    _modules << theme;
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
        QFrame *lineSplitter = CellUiGlobal::getLine(Cell::LineType::HLine);
        QHBoxLayout *layout = new QHBoxLayout;
        layout->setContentsMargins(10, 0, 10, 0);
        layout->addWidget(lineSplitter);
        mainBlockLayout->addLayout(layout);
        blockHeight += 1;
        setFixedHeight(blockHeight + 25);
    }

    _modules << item;
}

void customOptionBlock::setMainBlockBrightDarkModeColor(const CellVariant b, const CellVariant d)
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

void customOptionBlock::mousePressEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton){
        qDebug() << "block clicked";
        emit clicked(_theme);
        e->accept();
    }else
        e->ignore();
}
