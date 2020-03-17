#include "HomeStackGrid.h"

#include "../CustomBaseWidgets/customScrollBlock.h"
#include "../CustomBaseWidgets/customScrollArea.h"
#include "../CustomBaseWidgets/ButtonWithIcon.h"
#include "../../CellCore/Kits/CellUtility.h"

#include <QAbstractButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

HomeStackGrid::HomeStackGrid(QWidget *parent) noexcept:
    customFrame(customFrame::Type::Regular, parent),
    mainLayout(new QVBoxLayout(this)),
    btnDone(new ButtonWithIcon(customButton::Dynamic, this)),
    btnLayout(new QHBoxLayout),
    scrollArea(new customScrollArea(this)),
    scrollWidget(new customFrame(customFrame::Type::Regular)),
    widgetLayout(new QVBoxLayout(scrollWidget)),
    blockWorkShop(new customScrollBlock(CHAR2STR("Workshop"))),
    blockDeepSense(new customScrollBlock(CHAR2STR("Deepsense")))
{
    init();
    setEventConnections();
}

void HomeStackGrid::init()
{
    // Set Button Layout
    btnDone->setBrightDarkColor(Cell::CGL218, Cell::CGL45);
    btnDone->setBrightHoveringColor(Cell::CGL255);
    btnDone->setDarkHoveringColor(Cell::CGL100);
    btnDone->setAnimationDuration(250);
    btnDone->setFixedSize(100, 40);
    btnDone->initModules(CHAR2STR("iconDone"), 25, 25);

    btnLayout->setContentsMargins(15, 0, 0, 0);
    btnLayout->setAlignment(Qt::AlignmentFlag::AlignLeft);
    btnLayout->addWidget(btnDone);

    mainLayout->setMargin(0);
    mainLayout->setSpacing(15);
    mainLayout->addWidget(scrollArea);
    mainLayout->addLayout(btnLayout);

    // Set Scroll Area.
    blockWorkShop->setBrightDarkColor(Cell::CGL247, Cell::CGL30);
    blockDeepSense->setBrightDarkColor(Cell::CGL247, Cell::CGL30);
    blockWorkShop->addExclusiveBlock(blockDeepSense);

    widgetLayout->setAlignment(Qt::AlignmentFlag::AlignTop);
    widgetLayout->setContentsMargins(0, 0, 20, 0);
    widgetLayout->setSpacing(50);
    widgetLayout->addWidget(blockWorkShop);
    widgetLayout->addWidget(blockDeepSense);

    scrollWidget->setBrightDarkColor(Cell::CGL247, Cell::CGL30);
    scrollWidget->setLayout(widgetLayout);

    CellUiGlobal::loader.setFileName(CHAR2STR("scrollBar.css"));
    scrollArea->setStyleSheet(CellUiGlobal::loader.content());
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    scrollArea->setWidget(scrollWidget);

    CellWidgetGlobalInterface::_modules << blockWorkShop << blockDeepSense
                                        << scrollWidget;
}

void HomeStackGrid::setEventConnections()
{
    connect(blockWorkShop, &customScrollBlock::clicked, [=](const QString &name, int ID){
        currID = ID;
        currBlock = name;
    });
    connect(btnDone, &QPushButton::clicked, [=]{
        currBlock == CMPSTR("Deepsense")?
            emit openFileByPath(true,  DSMap[currID].path() + "//" + DSMap[currID].name() + ".workshop"):
            emit openFileByPath(false, WSMap[currID].path() + "//" + WSMap[currID].name() + ".workshop");
    });
}

void HomeStackGrid::insertProject(const CellProjectEntity &entity)
{
    static unsigned DSCount(1);
    static unsigned WSCount(1);

    switch(entity.type()){
    case CellProjectEntity::CellDeepLearning:
        WSMap[WSCount++] = entity;
        blockWorkShop->addItem(entity.name(), CHAR2STR("iconPJWS"), 180, 155);
        break;
    case CellProjectEntity::Empty:
        WSMap[WSCount++] = entity;
        blockWorkShop->addItem(entity.name(), CHAR2STR("iconPJWS"), 180, 155);
        break;
    case CellProjectEntity::CPP:
        WSMap[WSCount++] = entity;
        blockWorkShop->addItem(entity.name(), CHAR2STR("iconPJWS"), 180, 155);
        break;
    case CellProjectEntity::Python:
        WSMap[WSCount++] = entity;
        blockWorkShop->addItem(entity.name(), CHAR2STR("iconPJWS"), 180, 155);
        break;
    case CellProjectEntity::ImageClassify:
        DSMap[DSCount++] = entity;
        blockDeepSense->addItem(entity.name(), CHAR2STR("iconClassifyPic"), 180, 154);
        break;
    case CellProjectEntity::ObjectDetect:
        DSMap[DSCount++] = entity;
        blockDeepSense->addItem(entity.name(), CHAR2STR("iconObjectDetect"), 180, 155);
        break;
    case CellProjectEntity::PredictEarthquake:
        DSMap[DSCount++] = entity;
        blockDeepSense->addItem(entity.name(), CHAR2STR("iconPredictEar"), 180, 154);
        break;
    }
}
