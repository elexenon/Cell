// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "LauncherHomepage.h"
#include "ui_LauncherHomepage.h"
#include "../../CellCore/Kits/StyleSheetLoader.hpp"
#include "../CustomBaseWidgets/customOptionBlock.h"

#include <QScrollBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QHeaderView>
#include <QComboBox>
#include <QButtonGroup>
#include <QTableView>
#include <QStackedWidget>
#include <QStandardItem>
#include <qstandarditemmodel.h>

using namespace CellUiConst;

LauncherHomepage::LauncherHomepage(QWidget *parent) :
    QWidget(parent),
    mainLayout(new QVBoxLayout(this)),
    stackedWidget(new QStackedWidget(this)),
    tableView(new QTableView(stackedWidget)),
    scrollArea(new QScrollArea(stackedWidget)),
    btnGrid(new QPushButton(this)),
    btnList(new QPushButton(this)),
    iconRecentPJ(new QLabel(this)),
    labelRecentPJ(new QLabel(this))
{
    Init();
    setEventConnections();
}

void LauncherHomepage::Init()
{
    // Set HLayout_Btns.
    CellEntityTools::styleSheetLoader->setStyleSheetName(CHAR2STR("LauncherHomeGridBtn_Bright.css"));
    btnGrid->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());
    btnGrid->setCheckable(true);
    btnGrid->setFixedSize(51,41);

    CellEntityTools::styleSheetLoader->setStyleSheetName(CHAR2STR("LauncherHomeListBtn_Bright.css"));
    btnList->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());
    btnList->setCheckable(true);
    btnList->setFixedSize(51,41);

    QHBoxLayout *HLayout_Btns = new QHBoxLayout;
    HLayout_Btns->addWidget(btnGrid);
    HLayout_Btns->addWidget(btnList);

    // Set HLayout_Row1.
    CellUiGlobal::setCustomTextLabel(labelRecentPJ, CHAR2STR("Microsoft YaHei UI Light"), 19, CHAR2STR("近期使用"));

    CellEntityTools::styleSheetLoader->setStyleSheetName(CHAR2STR("LauncherHomeIconRecentPJBright.css"));
    iconRecentPJ->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());
    iconRecentPJ->setFixedSize(19, 19);

    QHBoxLayout *HLayout_Row1 = new QHBoxLayout;
    HLayout_Row1->setSpacing(7);
    HLayout_Row1->addWidget(iconRecentPJ);
    HLayout_Row1->addWidget(labelRecentPJ);
    HLayout_Row1->addStretch();
    HLayout_Row1->addLayout(HLayout_Btns);

    // Set ScrollArea.
    scrollArea->setFrameShape(QFrame::Shape::NoFrame);
    CellEntityTools::styleSheetLoader->setStyleSheetName(CHAR2STR("LauncherHomeScrollBar_Bright.css"));
    QScrollBar *verticalBar = scrollArea->verticalScrollBar();
    verticalBar->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

    // Set ButtonGroup For Button Grid And List.
    QButtonGroup *btnGroup = new QButtonGroup(this);
    btnGroup->setExclusive(true);
    btnGroup->addButton(btnGrid);
    btnGroup->addButton(btnList);
    btnList->setChecked(true);

    // Set TableView.
    initTableView();

    // Set StackedWidget.
    stackedWidget->addWidget(tableView);
    stackedWidget->addWidget(scrollArea);
    stackedWidget->setCurrentIndex(0);

    // set MainLayout.
    mainLayout->setSpacing(20);
    mainLayout->addLayout(HLayout_Row1);
    mainLayout->addWidget(stackedWidget);
    mainLayout->setContentsMargins(4, 20, 15, 10);

    customOptionBlock *block = new customOptionBlock(nullptr);
    block->setFixedSize(881,300);
}

void LauncherHomepage::setEventConnections()
{
    connect(btnGrid, &QPushButton::clicked, this, &LauncherHomepage::Btn_grid_clicked);
    connect(btnList, &QPushButton::clicked, this, &LauncherHomepage::Btn_list_clicked);
}

void LauncherHomepage::initTableView()
{
    QStringList headersList;
    headersList << CHAR2STR("名称") << CHAR2STR("修改时间") << CHAR2STR("大小") << CHAR2STR("类型");
    QStandardItemModel *itemModel = new QStandardItemModel;
    itemModel->setHorizontalHeaderLabels(headersList);
    itemModel->setItem(0, 0, new QStandardItem("流体模拟"));
    itemModel->setItem(0, 1, new QStandardItem("2020-01-28"));
    itemModel->setItem(0, 2, new QStandardItem("758Kb"));
    itemModel->setItem(0, 3, new QStandardItem("Cell DeepLearning"));
    itemModel->setItem(1, 0, new QStandardItem("基于Cell DeepLearning的地震预测系统"));
    itemModel->setItem(1, 1, new QStandardItem("2020-01-31"));
    itemModel->setItem(1, 2, new QStandardItem("1.5MB"));
    itemModel->setItem(1, 3, new QStandardItem("Cell DeepLearning"));
    itemModel->setItem(2, 0, new QStandardItem("Identity Cat Photos"));
    itemModel->setItem(2, 1, new QStandardItem("2020-02-05"));
    itemModel->setItem(2, 2, new QStandardItem("109Kb"));
    itemModel->setItem(2, 3, new QStandardItem("Cell DeepLearning"));
    itemModel->setItem(3, 0, new QStandardItem("噪声分析"));
    itemModel->setItem(3, 1, new QStandardItem("2020-01-09"));
    itemModel->setItem(3, 2, new QStandardItem("2.9MB"));
    itemModel->setItem(3, 3, new QStandardItem("Cell DeepLearning"));

    using CellEntityTools::styleSheetLoader;
    styleSheetLoader->setStyleSheetName(CHAR2STR("TreeViewBrightMode.css"));
    tableView->setStyleSheet(styleSheetLoader->styleSheet());

    tableView->setFrameShape(QFrame::NoFrame);
    tableView->setFont(QFont(CHAR2STR("Microsoft YaHei UI Light")));
    tableView->setAlternatingRowColors(true);
    tableView->setShowGrid(false);
    tableView->setSortingEnabled(true);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setModel(itemModel);
    tableView->verticalHeader()->hide();
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->horizontalHeader()->setFont(QFont(CHAR2STR("Microsoft YaHei UI Light")));
}

void LauncherHomepage::setColorScheme(CellUiGlobal::COLOR_SCHEME mode)
{
    if(mode == m_mode) return;
    m_mode = mode;
    if(mode == CellUiGlobal::COLOR_SCHEME::_DARK){
        CellUiGlobal::multiModulesOneStyleSheet({labelRecentPJ},
                                         CHAR2STR("QLabel{background-color:#1F1E1F; color:#FFFFFF;}"));

        CellEntityTools::styleSheetLoader->setStyleSheetName(CHAR2STR("LauncherHomeScrollBar_Dark.css"));
        QScrollBar *verticalBar = scrollArea->verticalScrollBar();
        verticalBar->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

        CellEntityTools::styleSheetLoader->setStyleSheetName(CHAR2STR("LauncherHomeGridBtn_Dark.css"));
        btnGrid->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

        CellEntityTools::styleSheetLoader->setStyleSheetName(CHAR2STR("LauncherHomeListBtn_Dark.css"));
        btnList->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());
    }
    else{
        CellUiGlobal::multiModulesOneStyleSheet({labelRecentPJ},
                                         CHAR2STR("QLabel{background-color:#F7F7F7; color:#000000;}"));

        CellEntityTools::styleSheetLoader->setStyleSheetName(CHAR2STR("LauncherHomeScrollBar_Bright.css"));
        QScrollBar *verticalBar = scrollArea->verticalScrollBar();
        verticalBar->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

        CellEntityTools::styleSheetLoader->setStyleSheetName(CHAR2STR("LauncherHomeGridBtn_Bright.css"));
        btnGrid->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());
        CellEntityTools::styleSheetLoader->setStyleSheetName(CHAR2STR("LauncherHomeListBtn_Bright.css"));
        btnList->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());
    }
}

void LauncherHomepage::Btn_grid_clicked()
{
    stackedWidget->setCurrentIndex(1);
}

void LauncherHomepage::Btn_list_clicked()
{
    stackedWidget->setCurrentIndex(0);
}
