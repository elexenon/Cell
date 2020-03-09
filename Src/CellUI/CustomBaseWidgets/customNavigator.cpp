#include "customNavigator.h"
#include "ButtonWithText.h"
#include "customOptionBlock.h"
#include "CellWidgetGlobalInterface.h"
#include "../../CellCore/Kits/CellGlobalMacros.h"

#include <cassert>
#include <QButtonGroup>
#include <QVBoxLayout>

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
    connect(block, &customOptionBlock::clicked, this, &customNavigator::setCurr);

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
    tmp->setFixedHeight(35);
    mainLayout->addWidget(tmp);
    btnGroup->addButton(tmp, buttonID);
    blockBtnMap[block->_theme] = buttonID++;

    if(!firstClicked){
        tmp->click();
        firstClicked = true;
    }
    _modules << tmp;
}

void customNavigator::setTopMargin(int value)
{
    auto margin = mainLayout->contentsMargins();
    margin.setTop(value);
    mainLayout->setContentsMargins(margin);
}

void customNavigator::setCurr(const QString &name){
    btnGroup->button(blockBtnMap[name])->click();
}
