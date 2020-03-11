// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "customNavigator.h"
#include "ButtonWithText.h"
#include "customOptionBlock.h"
#include "CellWidgetGlobalInterface.h"
#include "../../CellCore/Kits/CellGlobalMacros.h"

#include <cassert>
#include <QButtonGroup>
#include <QVBoxLayout>

int customNavigator::buttonHeight = 35;

customNavigator::customNavigator(QWidget *parent):
    customFrame(customFrame::Type::Regular, parent),
    mainLayout(new QVBoxLayout(this)),
    btnGroup(new QButtonGroup(this))
{
    init();
}

void customNavigator::init()
{
    setFixedWidth(110);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->setAlignment(Qt::AlignmentFlag::AlignTop);
    btnGroup->setExclusive(true);

    if(typeid(CellWidgetGlobalInterface*) == typeid(this->parentWidget()))
        setBrightDarkColor(dynamic_cast<CellWidgetGlobalInterface*>(this->parentWidget())->brightColor(),
                                dynamic_cast<CellWidgetGlobalInterface*>(this->parentWidget())->darkColor());
    else
        setBrightDarkColor(Cell::CGL247, Cell::CGL30);
}

void customNavigator::jointBlock(const customOptionBlock *block)
{
    assert(block);
    static unsigned buttonID(1);
    static bool firstClicked(false);
    connect(block, &optionBlockBase::entered, this, &customNavigator::setCurr);

    // Add New Button Into Layout.
    ButtonWithText *tmp = new ButtonWithText(customButton::Type::Checkable, this);
    if(typeid(CellWidgetGlobalInterface*) == typeid(this->parentWidget()))
        tmp->setBrightDarkColor(dynamic_cast<CellWidgetGlobalInterface*>(this->parentWidget())->brightColor(),
                                dynamic_cast<CellWidgetGlobalInterface*>(this->parentWidget())->darkColor());
    else
        tmp->setBrightDarkColor(this->brightColor(), this->darkColor());
    tmp->setBrightCheckedColor(Cell::CGL230);
    tmp->setDarkCheckedColor(Cell::CGL100);
    tmp->setNaviBar();
    tmp->initModules(block->_theme, 16);
    tmp->setFixedHeight(customNavigator::buttonHeight);
    mainLayout->addWidget(tmp);
    btnGroup->addButton(tmp, buttonID);
    blockBtnMap[block->_theme] = buttonID++;

    if(!firstClicked){
        tmp->click();
        firstClicked = true;
    }
    CellWidgetGlobalInterface::_modules << tmp;
}

void customNavigator::setTopMargin(int value)
{
    auto margin = mainLayout->contentsMargins();
    margin.setTop(value);
    mainLayout->setContentsMargins(margin);
}

void customNavigator::setButtonHeight(int value){
    customNavigator::buttonHeight = value;
    if(blockBtnMap.isEmpty()) return;
    QMap<QString, unsigned>::const_iterator it;
    for(it = blockBtnMap.constBegin();it != blockBtnMap.constEnd();it ++)
        btnGroup->button(it.value())->setFixedHeight(value);
}

void customNavigator::setCurr(const QString &name){
    btnGroup->button(blockBtnMap[name])->click();
}
