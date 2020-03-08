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
    customFrame::init();
    setFixedWidth(80);
    mainLayout->setSpacing(10);
    mainLayout->setMargin(0);
    mainLayout->setAlignment(Qt::AlignmentFlag::AlignTop);
    btnGroup->setExclusive(true);

    if(typeid(CellWidgetGlobalInterface*) == typeid(this->parentWidget()))
        setBrightDarkColor(dynamic_cast<CellWidgetGlobalInterface*>(this->parentWidget())->brightColor(),
                                dynamic_cast<CellWidgetGlobalInterface*>(this->parentWidget())->darkModeColor());
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
                                dynamic_cast<CellWidgetGlobalInterface*>(this->parentWidget())->darkModeColor());
    else
        tmp->setBrightDarkColor(Cell::CGL247, Cell::CGL30);
    tmp->setBrightCheckedColor(Cell::CGL230);
    tmp->setDarkCheckedColor(Cell::CGL130);
    tmp->setNaviBar();
    tmp->initModules(CHAR2STR("通用"), 16);
    tmp->setFixedHeight(20);
    mainLayout->addWidget(tmp);
    btnGroup->addButton(tmp, buttonID);
    blockBtnMap[block->_theme] = buttonID++;

    if(!firstClicked){
        tmp->click();
        firstClicked = true;
    }
    _modules << tmp;
}

void customNavigator::setCurr(const QString &name){
    btnGroup->button(blockBtnMap[name])->click();
}
