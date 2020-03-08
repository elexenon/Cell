#include "customNavigator.h"
#include "ButtonWithText.h"
#include "customOptionBlock.h"
#include "CellWidgetGlobalInterface.h"
#include "../../CellCore/Kits/CellGlobalMacros.h"

#include <cassert>
#include <QButtonGroup>
#include <QVBoxLayout>

customNavigator::customNavigator(QWidget *parent):
    QWidget(parent),
    mainLayout(new QVBoxLayout(this)),
    btnGroup(new QButtonGroup(this))
{
    init();
}

void customNavigator::init()
{
    setStyleSheet(CHAR2STR("background:transparent;"));
    setFixedWidth(80);
    mainLayout->setSpacing(10);
    mainLayout->setMargin(0);
    mainLayout->setAlignment(Qt::AlignmentFlag::AlignTop);
    btnGroup->setExclusive(true);
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
        tmp->setBrightDarkModeColor(dynamic_cast<CellWidgetGlobalInterface*>(this->parentWidget())->brightModeColor(),
                                dynamic_cast<CellWidgetGlobalInterface*>(this->parentWidget())->darkModeColor());
    else
        tmp->setBrightDarkModeColor(Cell::CGL247, Cell::CGL30);
    tmp->setBrightModeCheckedColor(Cell::CGL230);
    tmp->setDarkModeCheckedColor(Cell::CGL130);
    tmp->setNaviBar();
    tmp->init(CHAR2STR("通用"), 16);
    tmp->setFixedHeight(20);
    mainLayout->addWidget(tmp);
    btnGroup->addButton(tmp, buttonID);
    btns.append(tmp);

    blockBtnMap[block->_theme] = buttonID++;

    if(!firstClicked){
        tmp->click();
        firstClicked = true;
    }
}

void customNavigator::setColorScheme(Cell::ColorScheme mode)
{
    for(auto & e : btns) e->setColorScheme(mode);
}

void customNavigator::setCurr(const QString &name)
{
    btnGroup->button(blockBtnMap[name])->click();
}
