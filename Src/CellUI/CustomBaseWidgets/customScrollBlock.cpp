// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "../../CellCore/Kits/CellUtility.h" // CellUiGlobal
#include "../../CellCore/Kits/CellGlobalMacros.h"
#include "ButtonWithIcon.h"
#include "customScrollBlock.h"
#include "customScrollBlockItem.h"
#include "customFlowLayout.h"

#include <QVBoxLayout>
#include <QButtonGroup>

unsigned customScrollBlock::itemSpacing = 15;

customScrollBlock::customScrollBlock(const QString &name, QWidget *parent):
    optionBlockBase(name, parent),
    flowLayout(new customFlowLayout(itemSpacing, itemSpacing, itemSpacing)),
    btnGroup(new QButtonGroup(this))
{
    init();
    setEventConnections();
}

customScrollBlock::~customScrollBlock(){
    CellSafeDelete(blocks)
}

void customScrollBlock::init()
{
    btnGroup->setExclusive(true);
    mainLayout->addWidget(CellUiGlobal::getLine(Cell::LineType::HLine));
    mainLayout->addLayout(flowLayout);
}

void customScrollBlock::setEventConnections(){
    connect(btnGroup, static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked), [=](int id){
        emit clicked(_theme, id);
    });
}

void customScrollBlock::addItem(const QString &tag)
{
    customScrollBlockItem *item = new customScrollBlockItem(this);
    item->initModules(tag, CHAR2STR("iconMaximize"), 17, 14);

    flowLayout->addWidget(item);

    CellWidgetGlobalInterface::_modules << item;

    btnGroup->addButton(item->btn, buttonCount++);

    if(!btnGroup->button(1)->isChecked())
        item->btn->click();
}

inline
void customScrollBlock::setExclusive(bool value){
    btnGroup->setExclusive(value);
}

void customScrollBlock::setButtonsChecked(bool checked)
{
    if(btnGroup->exclusive()) return;
    for(auto & e : btnGroup->buttons())
        e->setChecked(checked);
}

void customScrollBlock::processBlocks(const QString &theme, int buttonID)
{
    (void)buttonID;
    for(auto & e : *blocks)
        if(e->_theme == theme)
            e->setExclusive(true);
        else{
            e->setExclusive(false);
            e->setButtonsChecked(false);
        }
}

void customScrollBlock::addExclusiveBlock(customScrollBlock *block)
{
    if(blocks == nullptr) {
        blocks = new QVector<customScrollBlock*>;
        blocks->append(this);
        connect(this, &customScrollBlock::clicked, this, &customScrollBlock::processBlocks);
    }
    blocks->append(block);
    connect(block, &customScrollBlock::clicked, this, &customScrollBlock::processBlocks);
    btnGroup->button(1)->click();
}
