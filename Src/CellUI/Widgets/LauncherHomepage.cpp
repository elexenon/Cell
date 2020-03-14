// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "LauncherHomepage.h"
#include "../CustomBaseWidgets/customOptionBlock.h"
#include "../CustomBaseWidgets/ButtonWithIcon.h"
#include "../../CellCore/CellSqlManager.h"
#include "../../CellCore/CellProjectEntity.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
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
    btnGrid(new ButtonWithIcon(customButton::Checkable, this)),
    btnList(new ButtonWithIcon(customButton::Checkable, this)),
    iconRecentPJ(new QLabel(this)),
    labelRecentPJ(new QLabel(this))
{
    init();
    setEventConnections();
}

void LauncherHomepage::init()
{
    // Set HLayout_Btns.
    btnGrid->setBrightDarkColor(Cell::CGL247, Cell::CGL30);
    btnGrid->setBrightCheckedColor(Cell::CGL218);
    btnGrid->setDarkCheckedColor(Cell::CGL100);
    btnGrid->initModules(CHAR2STR("iconGrid"), 23, 21);
    btnGrid->setFixedSize(51,41);

    btnList->setBrightDarkColor(Cell::CGL247, Cell::CGL30);
    btnList->setBrightCheckedColor(Cell::CGL218);
    btnList->setDarkCheckedColor(Cell::CGL100);
    btnList->initModules(CHAR2STR("iconList"), 27, 20);
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
    mainLayout->setContentsMargins(4, 20, 20, 25);
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
    tableView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
}

void LauncherHomepage::setColorScheme(Cell::ColorScheme mode)
{
    if(mode == mMode) return;
    mMode = mode;

    const QString labelQss = (mode == Cell::ColorScheme::Bright ? "QLabel{background:transparent; color:rgb(70,70,70);}":
                                                              "QLabel{background:transparent; color:white;}");

    const QString IconQss = (mode == Cell::ColorScheme::Bright ? "LauncherHomeIconRecentPJBright.css":
                                                              "LauncherHomeIconRecentPJDark.css");

    CellUiGlobal::loader.setFileName(IconQss);
    iconRecentPJ->setStyleSheet(CellUiGlobal::loader.content());

    btnGrid->setColorScheme(mode);
    btnList->setColorScheme(mode);

    CellUiGlobal::multiModulesOneStyleSheet({labelRecentPJ},labelQss);
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
    CellSafeDelete(itemList);
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
