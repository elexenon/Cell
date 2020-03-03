// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "LauncherHomepage.h"
#include "../CustomBaseWidgets/customOptionBlock.h"
#include "../../CellCore/CellSqlManager.h"
#include "../../CellCore/CellProjectEntity.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QHeaderView>
#include <QComboBox>
#include <QButtonGroup>
#include <QTableView>
#include <QStackedWidget>
#include <QStandardItem>
#include <QStandardItemModel>

using namespace CellUiLiteral;

LauncherHomepage::LauncherHomepage(QWidget *parent) :
    QWidget(parent),
    mainLayout(new QVBoxLayout(this)),
    stackedWidget(new QStackedWidget(this)),
    tableView(new QTableView(stackedWidget)),
    itemModel(new QStandardItemModel),
    btnGrid(new QPushButton(this)),
    btnList(new QPushButton(this)),
    iconRecentPJ(new QLabel(this)),
    labelRecentPJ(new QLabel(this))
{
    init();
    setEventConnections();
}

void LauncherHomepage::init()
{
    // Set HLayout_Btns.
    CellUiGlobal::loader.setFileName(CHAR2STR("LauncherHomeGridBtn_Bright.css"));
    btnGrid->setStyleSheet(CellUiGlobal::loader.content());
    btnGrid->setCheckable(true);
    btnGrid->setFixedSize(51,41);

    CellUiGlobal::loader.setFileName(CHAR2STR("LauncherHomeListBtn_Bright.css"));
    btnList->setStyleSheet(CellUiGlobal::loader.content());
    btnList->setCheckable(true);
    btnList->setFixedSize(51,41);

    QHBoxLayout *HLayout_Btns = new QHBoxLayout;
    HLayout_Btns->addWidget(btnGrid);
    HLayout_Btns->addWidget(btnList);

    // Set HLayout_Row1.
    CellUiGlobal::setCustomTextLabel(labelRecentPJ, CHAR2STR("Microsoft YaHei UI Light"), 19, CHAR2STR("近期使用"));

    CellUiGlobal::loader.setFileName(CHAR2STR("LauncherHomeIconRecentPJBright.css"));
    iconRecentPJ->setStyleSheet(CellUiGlobal::loader.content());
    iconRecentPJ->setFixedSize(19, 19);

    QHBoxLayout *HLayout_Row1 = new QHBoxLayout;
    HLayout_Row1->setSpacing(7);
    HLayout_Row1->addWidget(iconRecentPJ);
    HLayout_Row1->addWidget(labelRecentPJ);
    HLayout_Row1->addStretch();
    HLayout_Row1->addLayout(HLayout_Btns);

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
    //stackedWidget->addWidget(); TODO
    stackedWidget->setCurrentIndex(0);

    // set MainLayout.
    mainLayout->setSpacing(20);
    mainLayout->addLayout(HLayout_Row1);
    mainLayout->addWidget(stackedWidget);
    mainLayout->setContentsMargins(4, 20, 15, 10);
}

void LauncherHomepage::setEventConnections()
{
    connect(btnGrid, &QPushButton::clicked, this, &LauncherHomepage::btnGridClicked);
    connect(btnList, &QPushButton::clicked, this, &LauncherHomepage::btnListClicked);
    connect(tableView, &QTableView::doubleClicked, this, &LauncherHomepage::tableDoubleClicked);
}

void LauncherHomepage::initTableView()
{
    QStringList headersList;
    headersList << CHAR2STR("名称") << CHAR2STR("修改时间") << CHAR2STR("类型") << CHAR2STR("路径");
    itemModel->setHorizontalHeaderLabels(headersList);
    updateDatas();
    // Set TableView.
     
    CellUiGlobal::loader.setFileName(CHAR2STR("TableViewBrightMode.css"));
    tableView->setStyleSheet(CellUiGlobal::loader.content());
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

void LauncherHomepage::setColorScheme(Cell::ColorScheme mode)
{
    if(mode == m_mode) return;
    m_mode = mode;

    const QString labelQss = (mode == Cell::ColorScheme::Bright ? "QLabel{background:transparent; color:rgb(70,70,70);}":
                                                              "QLabel{background:transparent; color:white;}");
    const QString gridQssFile =  (mode == Cell::ColorScheme::Bright ? "LauncherHomeGridBtn_Bright.css":
                                                                  "LauncherHomeGridBtn_Dark.css");
    const QString listQssFile =  (mode == Cell::ColorScheme::Bright ? "LauncherHomeListBtn_Bright.css":
                                                                  "LauncherHomeListBtn_Dark.css");

    CellUiGlobal::multiModulesOneStyleSheet({labelRecentPJ},labelQss);
    CellUiGlobal::loader.setFileName(gridQssFile);
    btnGrid->setStyleSheet(CellUiGlobal::loader.content());
    CellUiGlobal::loader.setFileName(listQssFile);
    btnList->setStyleSheet(CellUiGlobal::loader.content());
}

void LauncherHomepage::updateDatasByWS(CellProjectEntity &entity)
{
    QList<QStandardItem*> itemList;
    itemList.append(new QStandardItem(entity.name()));
    itemList.append(new QStandardItem(entity.modifiedTime()));
    itemList.append(new QStandardItem(CellProjectEntity::getType(entity.type())));
    itemList.append(new QStandardItem(entity.path()));
    itemModel->insertRow(0, itemList);
}

void LauncherHomepage::updateDatas()
{
    // Start Sql.
    CellSqlManager recentPJSql;
    recentPJSql.setDataBase("CellDB.db");
    if(!recentPJSql.tableExists("RecentPJ")){
        const char *sqlSentence =
                                "CREATE TABLE RecentPJ("
                                "Name	       TEXT  PRIMARY KEY  NOT NULL,"
                                "ModifiedTime  TEXT   			  NOT NULL,"
                                "Type		   TEXT			      NOT NULL,"
                                "Path		   TEXT			      NOT NULL);";
        recentPJSql.createTable(sqlSentence);
    }
    // CellSqlManager Will Fetch A Row Of Table "RecentPJ" Once
    // A "While" Circle Is Over.
    QList<QStandardItem*> *itemList = new QList<QStandardItem*>;
    while(recentPJSql.fetchRecentPJRow(itemList)){
        if(itemList->isEmpty()) continue;
        itemModel->appendRow(*itemList);
    }
    SafeDelete(itemList);
}

void LauncherHomepage::btnGridClicked()
{
    stackedWidget->setCurrentIndex(1);
}

void LauncherHomepage::btnListClicked()
{
    stackedWidget->setCurrentIndex(0);
}

void LauncherHomepage::tableDoubleClicked(const QModelIndex &index)
{
    qDebug() << index.siblingAtColumn(3).data();
    emit getProjectPath(index.siblingAtColumn(3).data().toString() + "//" +
                        index.siblingAtColumn(0).data().toString() + ".workshop");
}
