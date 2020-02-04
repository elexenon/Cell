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
#include <QComboBox>

using namespace CellUiConst;

LauncherHomepage::LauncherHomepage(QWidget *parent) :
    QWidget(parent),
    mainLayout(new QVBoxLayout(this)),
    scrollArea(new QScrollArea(this)),
    BtnGrid(new QPushButton(scrollArea)),
    BtnList(new QPushButton(scrollArea)),
    labelRecentPJ(new QLabel(scrollArea)),
    labelSort(new QLabel(scrollArea)),
    splitterLine(new QFrame(scrollArea)),
    cBoxSort(new QComboBox)
{
    Init();
}

void LauncherHomepage::Init()
{
    QFont font(CHAR2STR("微软雅黑 Light"));
    font.setPixelSize(29);

    BtnGrid->setFixedSize(51,41);
    BtnList->setFixedSize(51,41);

    QHBoxLayout *HLayout_Btns = new QHBoxLayout;
    HLayout_Btns->addWidget(BtnGrid);
    HLayout_Btns->addWidget(BtnList);

    QHBoxLayout *HLayout_Row1 = new QHBoxLayout;
    HLayout_Row1->addWidget(labelRecentPJ);
    HLayout_Row1->addStretch();
    HLayout_Row1->addLayout(HLayout_Btns);

    QHBoxLayout *HLayout_Row2 = new QHBoxLayout;
    HLayout_Row2->addWidget(labelSort);
    HLayout_Row2->addWidget(splitterLine);
    HLayout_Row2->addWidget(cBoxSort);
    HLayout_Row2->addStretch();

    mainLayout->addLayout(HLayout_Row1);
    mainLayout->addLayout(HLayout_Row2);
    mainLayout->addWidget(scrollArea);
    mainLayout->setContentsMargins(4, 20, 15, 10);

    customOptionBlock *block = new customOptionBlock(nullptr);
    block->setFixedSize(881,300);
    QVBoxLayout *scrollAreaWidgetLayout = new QVBoxLayout;
    scrollAreaWidgetLayout->addWidget(block);
    scrollAreaWidgetLayout->setAlignment(Qt::AlignmentFlag::AlignTop);
    ui->scrollAreaWidgetContents_3->setLayout(scrollAreaWidgetLayout);

    CellEntityTools::styleSheetLoader->setStyleSheetName(CHAR2STR("LauncherHomeComboBox.css"));
    cBoxSort->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

    cBoxSort->setFont(QFont("Microsoft YaHei UI"));

    CellEntityTools::styleSheetLoader->setStyleSheetName(CHAR2STR("LauncherHomeGridBtn_Bright.css"));
    BtnGrid->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

    CellEntityTools::styleSheetLoader->setStyleSheetName(CHAR2STR("LauncherHomeListBtn_Bright.css"));
    BtnList->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

    font.setPixelSize(19);
    labelRecentPJ->setFont(font);

    font.setPixelSize(17);
    labelSort->setFont(font);
    labelSort->setStyleSheet(CHAR2STR("color:dadada;"));

    font.setPixelSize(14);
    cBoxSort->setFixedWidth(87);
    cBoxSort->setFont(font);

    CellEntityTools::styleSheetLoader->setStyleSheetName(CHAR2STR("LauncherHomeScrollBar_Bright.css"));
    QScrollBar *verticalBar = scrollArea->verticalScrollBar();
    verticalBar->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

}

void LauncherHomepage::setAllGraphBtnsUnchecked()
{
    BtnGrid->setChecked(false);
    BtnList->setChecked(false);
}

void LauncherHomepage::setColorScheme(CellUiGlobal::COLOR_SCHEME mode)
{
    if(mode == m_mode) return;
    m_mode = mode;
    if(mode == CellUiGlobal::COLOR_SCHEME::_DARK){
        CellUiGlobal::multiModulesOneStyleSheet({labelSort,labelRecentPJ},
                                         CHAR2STR("QLabel{background-color:#1F1E1F; color:#FFFFFF;}"));
        splitterLine->setStyleSheet("QFrame{border:none;background-color:#FFFFFF;"
                                "max-height : 21px;}");

        ui->scrollAreaWidgetContents_3->setStyleSheet("QWidget{background-color:#1F1E1F;}");

        CellEntityTools::styleSheetLoader->setStyleSheetName(CHAR2STR("LauncherHomeScrollBar_Dark.css"));
        QScrollBar *verticalBar = scrollArea->verticalScrollBar();
        verticalBar->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

        CellEntityTools::styleSheetLoader->setStyleSheetName(CHAR2STR("LauncherHomeGridBtn_Dark.css"));
        BtnGrid->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

        CellEntityTools::styleSheetLoader->setStyleSheetName(CHAR2STR("LauncherHomeListBtn_Dark.css"));
        BtnList->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());
    }
    else{
        CellUiGlobal::multiModulesOneStyleSheet({labelSort,labelRecentPJ},
                                         CHAR2STR("QLabel{background-color:#F7F7F7; color:#000000;}"));
        splitterLine->setStyleSheet(CHAR2STR("QFrame{border:none;background-color:#DADADA;max-height : 21px;}"));

        ui->scrollAreaWidgetContents_3->setStyleSheet("QWidget{background-color:rgb(247, 247, 247);}");

        CellEntityTools::styleSheetLoader->setStyleSheetName(CHAR2STR("LauncherHomeScrollBar_Bright.css"));
        QScrollBar *verticalBar = scrollArea->verticalScrollBar();
        verticalBar->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

        CellEntityTools::styleSheetLoader->setStyleSheetName(CHAR2STR("LauncherHomeGridBtn_Bright.css"));
        BtnGrid->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());
        CellEntityTools::styleSheetLoader->setStyleSheetName(CHAR2STR("LauncherHomeListBtn_Bright.css"));
        BtnList->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());
    }
}

void LauncherHomepage::on_Btn_grid_clicked()
{
    setAllGraphBtnsUnchecked();
    BtnGrid->setChecked(true);
}

void LauncherHomepage::on_Btn_list_clicked()
{
    setAllGraphBtnsUnchecked();
    BtnList->setChecked(true);
}
