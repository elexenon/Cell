#include "NewPJGUIModel.h"
#include "../CustomBaseWidgets/customFrame.h"
#include "../CustomBaseWidgets/customNavigator.h"
#include "../CustomBaseWidgets/customScrollBlock.h"
#include "../CustomBaseWidgets/customSmoothScrollArea.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

NewPJGUIModel::NewPJGUIModel(QWidget *parent):
    customFrame(customFrame::Type::Regular, parent),
    mainLayout(new QHBoxLayout(this)),
    navigator(new customNavigator(this)),
    scrollArea(new customSmoothScrollArea(this)),
    scrollWidget(new customFrame(customFrame::Type::Regular))
{
    init();
}

void NewPJGUIModel::init()
{
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(navigator);
    mainLayout->addWidget(scrollArea);

    // Set Scroll Area.
    customScrollBlock *block = new customScrollBlock(CHAR2STR("图像"), scrollWidget);
    block->setBrightDarkColor(Cell::CGL247, Cell::CGL45);
    block->addItem(CHAR2STR("图像分类"));
    block->addItem(CHAR2STR("对象分离"));

    customScrollBlock *block2 = new customScrollBlock(CHAR2STR("二值"), scrollWidget);
    block2->setBrightDarkColor(Cell::CGL247, Cell::CGL45);
    block2->addItem(CHAR2STR("地震预测"));

    block->addExclusiveBlock(block2);

    QVBoxLayout *widgetLayout = new QVBoxLayout(scrollWidget);
    widgetLayout->setAlignment(Qt::AlignmentFlag::AlignTop);
    widgetLayout->setSpacing(20);
    widgetLayout->setContentsMargins(20, 20, 20, 20);
    widgetLayout->addWidget(block);
    widgetLayout->addWidget(block2);
    scrollWidget->setBrightDarkColor(Cell::CGL247, Cell::CGL30);

    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    scrollArea->setWidget(scrollWidget);

    // Set navigator.
    navigator->setFixedWidth(150);
    navigator->setButtonHeight(45);

    navigator->jointBlock(block);
    navigator->jointBlock(block2);
}
