// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "LauncherHomepage.h"
#include "HomeStackGrid.h"
#include "HomeStackList.h"
#include "../CustomBaseWidgets/customLabel.h"
#include "../CustomBaseWidgets/ButtonWithIcon.h"
#include "../../CellCore/CellSqlManager.h"
#include "../../CellCore/CellProjectEntity.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QButtonGroup>
#include <QStackedWidget>

using namespace CellUiLiteral;

LauncherHomepage::LauncherHomepage(QWidget *parent) :
    QWidget(parent),
    mainLayout(new QVBoxLayout(this)),
    stackGrid(new HomeStackGrid(this)),
    stackList(new HomeStackList(this)),
    stackedWidget(new QStackedWidget(this)),
    btnGrid(new ButtonWithIcon(customButton::Checkable, this)),
    btnList(new ButtonWithIcon(customButton::Checkable, this)),
    iconRecentPJ(new QLabel(this)),
    labelRecentPJ(new customLabel(this))
{
    init();
    setEventConnections();
    updateDatas();
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

    QButtonGroup *btnGroup = new QButtonGroup(this);
    btnGroup->setExclusive(true);
    btnGroup->addButton(btnGrid, 1);
    btnGroup->addButton(btnList, 2);
    btnGroup->button(1)->click();

    QHBoxLayout *HLayout_Btns = new QHBoxLayout;
    HLayout_Btns->addWidget(btnGrid);
    HLayout_Btns->addWidget(btnList);

    // Set HLayout_Row1.
    labelRecentPJ->setBrightDarkColor(Cell::CGL70, Cell::CGL255);
    CellUiGlobal::setCustomTextLabel(labelRecentPJ, CHAR2STR("Microsoft YaHei UI Light"), 19, CHAR2STR("近期使用"));   
    iconRecentPJ->setFixedSize(19, 19);
    CellUiGlobal::setLabelPixmap(iconRecentPJ, CHAR2STR("iconRecentPJ"), 19, 19);

    QHBoxLayout *HLayout_Row1 = new QHBoxLayout;
    HLayout_Row1->setSpacing(7);
    HLayout_Row1->addWidget(iconRecentPJ);
    HLayout_Row1->addWidget(labelRecentPJ);
    HLayout_Row1->addStretch();
    HLayout_Row1->addLayout(HLayout_Btns);

    // Set Stack Grid.
    stackGrid->setBrightDarkColor(Cell::CGL247, Cell::CGL30);

    // Set Stack List
    stackList->setBrightDarkColor(Cell::CGL247, Cell::CGL30);

    // Set StackedWidget.
    stackedWidget->addWidget(stackGrid);
    stackedWidget->addWidget(stackList);

    // set MainLayout.
    mainLayout->setSpacing(20);
    mainLayout->addLayout(HLayout_Row1);
    mainLayout->addWidget(stackedWidget);
    mainLayout->setContentsMargins(4, 20, 20, 25);
}

void LauncherHomepage::setEventConnections()
{
    connect(btnGrid, &QPushButton::clicked, [=]{
        stackedWidget->setCurrentIndex(0);
    });
    connect(btnList, &QPushButton::clicked, [=]{
        stackedWidget->setCurrentIndex(1);
    });
    connect(stackList, &HomeStackList::openFileByPath, this, &LauncherHomepage::openFileByPath);
    connect(stackGrid, &HomeStackGrid::openFileByPath, this, &LauncherHomepage::openFileByPath);
}

void LauncherHomepage::setColorScheme(Cell::ColorScheme mode)
{
    if(mode == mMode) return;
    mMode = mode;

    labelRecentPJ->setColorScheme(mode);

    const QString iconFile = (mode == Cell::ColorScheme::Bright ? "iconRecentPJ":
                                                                  "iconRecentPJDark");
    CellUiGlobal::setLabelPixmap(iconRecentPJ, iconFile, 19, 19);

    btnGrid->setColorScheme(mode);
    btnList->setColorScheme(mode);
}

void LauncherHomepage::insertProject(const CellProjectEntity &entity)
{
    QList<QStandardItem*> itemList;
    itemList.append(new QStandardItem(entity.name()));
    itemList.append(new QStandardItem(entity.modifiedTime()));
    itemList.append(new QStandardItem(CellProjectEntity::getType(entity.type())));
    itemList.append(new QStandardItem(entity.path()));
    stackList->tableInsertRow(0, itemList);
    stackGrid->insertProject(entity);
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
        stackList->tableAppendRow(*itemList);
        stackGrid->insertProject(CellProjectEntity::convert(*itemList));
    }
    CellSafeDelete(itemList);
}
