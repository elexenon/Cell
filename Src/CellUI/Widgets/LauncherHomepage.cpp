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

#include <QScrollBar>
#include <QHBoxLayout>
#include <QVBoxLayout>

using namespace CellUiConst;

LauncherHomepage::LauncherHomepage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LauncherHomepage),
    m_mode(CellUiGlobal::COLOR_SCHEME::_BRIGHT)
{
    ui->setupUi(this);
    Init();
}

LauncherHomepage::~LauncherHomepage()
{
    delete ui;
}

void LauncherHomepage::Init()
{
    QFont font(QStringLiteral("微软雅黑 Light"));
    font.setPixelSize(29);
    ui->label_welcome->setFont(font);

    ui->Btn_grid->setFixedSize(51,41);
    ui->Btn_list->setFixedSize(51,41);

    QHBoxLayout *HLayout_Row1 = new QHBoxLayout;
    HLayout_Row1->addStretch(2);
    HLayout_Row1->addWidget(ui->label_welcome);
    HLayout_Row1->addStretch(3);

    QHBoxLayout *HLayout_Btns = new QHBoxLayout;
    HLayout_Btns->addWidget(ui->Btn_grid);
    HLayout_Btns->addWidget(ui->Btn_list);

    QHBoxLayout *HLayout_Row2 = new QHBoxLayout;
    HLayout_Row2->addWidget(ui->label_recentPJ);
    HLayout_Row2->addStretch();
    HLayout_Row2->addLayout(HLayout_Btns);

    QHBoxLayout *HLayout_Row3 = new QHBoxLayout;
    HLayout_Row3->addWidget(ui->label_sort);
    HLayout_Row3->addWidget(ui->line);
    HLayout_Row3->addWidget(ui->comboBox_sort);
    HLayout_Row3->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(HLayout_Row1);
    mainLayout->addLayout(HLayout_Row2);
    mainLayout->addLayout(HLayout_Row3);
    mainLayout->addWidget(ui->main_scrollArea);
    mainLayout->setContentsMargins(4, 13, 15, 10);

    setLayout(mainLayout);

    CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("LauncherHomeComboBox.css"));
    ui->comboBox_sort->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

    ui->comboBox_sort->setFont(QFont("Microsoft YaHei UI"));

    CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("LauncherHomeGridBtn_Bright.css"));
    ui->Btn_grid->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

    CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("LauncherHomeListBtn_Bright.css"));
    ui->Btn_list->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

    font.setPixelSize(19);
    ui->label_recentPJ->setFont(font);

    font.setPixelSize(17);
    ui->label_sort->setFont(font);
    ui->label_sort->setStyleSheet(QStringLiteral("color:dadada;"));

    font.setPixelSize(14);
    ui->comboBox_sort->setFixedWidth(87);
    ui->comboBox_sort->setFont(font);

    CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("LauncherHomeScrollBar_Bright.css"));
    QScrollBar *verticalBar = ui->main_scrollArea->verticalScrollBar();
    verticalBar->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

    CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("LauncherHome_OptionBlock_Bright.css"));
    ui->frame->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());
}

void LauncherHomepage::setAllGraphBtnsUnchecked()
{
    ui->Btn_grid->setChecked(false);
    ui->Btn_list->setChecked(false);
}

void LauncherHomepage::setColorScheme(CellUiGlobal::COLOR_SCHEME mode)
{
    if(mode == m_mode) return;
    m_mode = mode;
    if(mode == CellUiGlobal::COLOR_SCHEME::_DARK){
        CellUiGlobal::multiModulesOneStyleSheet({ui->label_welcome,ui->label_sort,ui->label_recentPJ},
                                         QStringLiteral("QLabel{background-color:#1F1E1F; color:#FFFFFF;}"));
        ui->line->setStyleSheet("QFrame{border:none;background-color:#FFFFFF;"
                                "max-height : 21px;}");
        CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("LauncherHome_OptionBlock_Dark.css"));
        ui->frame->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

        ui->scrollAreaWidgetContents_3->setStyleSheet("QWidget{background-color:#1F1E1F;}");

        CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("LauncherHomeScrollBar_Dark.css"));
        QScrollBar *verticalBar = ui->main_scrollArea->verticalScrollBar();
        verticalBar->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

        CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("LauncherHomeGridBtn_Dark.css"));
        ui->Btn_grid->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

        CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("LauncherHomeListBtn_Dark.css"));
        ui->Btn_list->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());
    }
    else{
        CellUiGlobal::multiModulesOneStyleSheet({ui->label_welcome,ui->label_sort,ui->label_recentPJ},
                                         QStringLiteral("QLabel{background-color:#F7F7F7; color:#000000;}"));
        ui->line->setStyleSheet(QStringLiteral("QFrame{border:none;background-color:#DADADA;max-height : 21px;}"));
        CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("LauncherHome_OptionBlock_Bright.css"));
        ui->frame->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

        ui->scrollAreaWidgetContents_3->setStyleSheet("QWidget{background-color:rgb(247, 247, 247);}");

        CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("LauncherHomeScrollBar_Bright.css"));
        QScrollBar *verticalBar = ui->main_scrollArea->verticalScrollBar();
        verticalBar->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

        CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("LauncherHomeGridBtn_Bright.css"));
        ui->Btn_grid->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());
        CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("LauncherHomeListBtn_Bright.css"));
        ui->Btn_list->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());
    }
}

void LauncherHomepage::on_Btn_grid_clicked()
{
    setAllGraphBtnsUnchecked();
    ui->Btn_grid->setChecked(true);
}

void LauncherHomepage::on_Btn_list_clicked()
{
    setAllGraphBtnsUnchecked();
    ui->Btn_list->setChecked(true);
}
