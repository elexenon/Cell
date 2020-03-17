#include "NewPJGUIModel.h"
#include "../CustomBaseWidgets/customFrame.h"
#include "../CustomBaseWidgets/customNavigator.h"
#include "../CustomBaseWidgets/customScrollBlock.h"
#include "../CustomBaseWidgets/customScrollArea.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

NewPJGUIModel::NewPJGUIModel(QWidget *parent):
    customFrame(customFrame::Type::Regular, parent),
    mainLayout(new QHBoxLayout(this)),
    navigator(new customNavigator(this)),
    scrollArea(new customScrollArea(this)),
    scrollWidget(new customFrame(customFrame::Type::Regular)),
    blockPic(new customScrollBlock(CHAR2STR("图像"), scrollWidget)),
    blockBinary(new customScrollBlock(CHAR2STR("二值"), scrollWidget))
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
    blockPic->setBrightDarkColor(Cell::CGL247, Cell::CGL30);
    blockPic->addItem(CHAR2STR("图像分类"), CHAR2STR("iconClassifyPic"), 180, 154);
    blockPic->addItem(CHAR2STR("对象探测"), CHAR2STR("iconObjectDetect"), 180, 155);

    blockBinary->setBrightDarkColor(Cell::CGL247, Cell::CGL30);
    blockBinary->addItem(CHAR2STR("地震预测"), CHAR2STR("iconPredictEar"), 180, 154);

    blockPic->addExclusiveBlock(blockBinary);

    QVBoxLayout *widgetLayout = new QVBoxLayout(scrollWidget);
    widgetLayout->setAlignment(Qt::AlignmentFlag::AlignTop);
    widgetLayout->setSpacing(20);
    widgetLayout->setContentsMargins(20, 20, 20, 20);
    widgetLayout->addWidget(blockPic);
    widgetLayout->addWidget(blockBinary);
    scrollWidget->setBrightDarkColor(Cell::CGL247, Cell::CGL30);

    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    scrollArea->setWidget(scrollWidget);

    // Set navigator.
    navigator->setFixedWidth(150);
    navigator->setButtonHeight(45);

    navigator->jointBlock(blockPic);
    navigator->jointBlock(blockBinary);

    CellWidgetGlobalInterface::_modules << blockPic << blockBinary << scrollWidget << navigator;
}

void NewPJGUIModel::setEventConnections()
{
    connect(blockPic, &customScrollBlock::clicked, [=](const QString&, int ID){
        CellProjectEntity::ProjectType type;
        switch(ID){
        case 1:
            type = CellProjectEntity::ProjectType::ImageClassify;
            break;
        case 2:
            type = CellProjectEntity::ProjectType::ObjectDetect;
            break;
        }
        emit typeSeleted(type);
    });
    connect(blockBinary, &customScrollBlock::clicked, [=](const QString&, int ID){
        CellProjectEntity::ProjectType type;
        switch(ID){
        case 1:
            type = CellProjectEntity::ProjectType::PredictEarthquake;
            break;
        }
        emit typeSeleted(type);
    });
}
