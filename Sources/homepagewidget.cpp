// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "Headers/homepagewidget.h"
#include "Headers/Kits/qstylesheetloader.hpp"
#include "ui_homepagewidget.h"

#include <QScrollBar>

using namespace Cell_Const;

HomePageWidget::HomePageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomePageWidget),
    m_mode(CellGlobal::COLOR_SCHEME::_BRIGHT)
{
    ui->setupUi(this);
    Init();
}

HomePageWidget::~HomePageWidget()
{
    delete ui;
}

void HomePageWidget::Init()
{
    ui->label_welcome->setFont(QFont(QStringLiteral("微软雅黑 Light"), 18));

    CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowComboBox.css"));
    ui->comboBox_sort->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

    ui->comboBox_sort->setFont(QFont("Microsoft YaHei UI"));

    CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowGridBtn_Bright.css"));
    ui->Btn_grid->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

    CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowListBtn_Bright.css"));
    ui->Btn_list->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

    ui->label_recentPJ->setFont(QFont(QStringLiteral("微软雅黑"), 12));

    ui->label_sort->setFont(QFont(QStringLiteral("微软雅黑 Light"), 10));
    ui->label_sort->setStyleSheet(QStringLiteral("color:dadada;"));

    CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("ScrollBar_Bright.css"));
    QScrollBar *verticalBar = ui->main_scrollArea->verticalScrollBar();
    verticalBar->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

    CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("Homepage_OptionBlock_bright.css"));
    ui->frame->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());
}

void HomePageWidget::setAllGraphBtnsUnchecked()
{
    ui->Btn_grid->setChecked(false);
    ui->Btn_list->setChecked(false);
}

void HomePageWidget::setColorScheme(CellGlobal::COLOR_SCHEME mode)
{
    if(mode == m_mode) return;
    if(mode == CellGlobal::COLOR_SCHEME::_DARK){
        m_mode = CellGlobal::COLOR_SCHEME::_DARK;
        CellGlobal::multiModulesOneStyleSheet({ui->label_welcome,ui->label_sort,ui->label_recentPJ},
                                         QStringLiteral("QLabel{background-color:#1F1E1F; color:#FFFFFF;}"));
        ui->line->setStyleSheet("QFrame{border:none;background-color:#FFFFFF;"
                                "max-height : 21px;}");
        CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("Homepage_OptionBlock_dark.css"));
        ui->frame->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

        ui->scrollAreaWidgetContents_3->setStyleSheet("QWidget{background-color:#1F1E1F;}");

        CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("ScrollBar_Dark.css"));
        QScrollBar *verticalBar = ui->main_scrollArea->verticalScrollBar();
        verticalBar->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

        CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowGridBtn_Dark.css"));
        ui->Btn_grid->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

        CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowListBtn_Dark.css"));
        ui->Btn_list->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());
    }
    else{
        m_mode = CellGlobal::COLOR_SCHEME::_BRIGHT;
        CellGlobal::multiModulesOneStyleSheet({ui->label_welcome,ui->label_sort,ui->label_recentPJ},
                                         QStringLiteral("QLabel{background-color:#F7F7F7; color:#000000;}"));
        ui->line->setStyleSheet(QStringLiteral("QFrame{border:none;background-color:#DADADA;max-height : 21px;}"));
        CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("Homepage_OptionBlock_bright.css"));
        ui->frame->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

        ui->scrollAreaWidgetContents_3->setStyleSheet("QWidget{background-color:rgb(247, 247, 247);}");

        CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("ScrollBar_Bright.css"));
        QScrollBar *verticalBar = ui->main_scrollArea->verticalScrollBar();
        verticalBar->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

        CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowGridBtn_Bright.css"));
        ui->Btn_grid->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());
        CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowListBtn_Bright.css"));
        ui->Btn_list->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());
    }
}

void HomePageWidget::on_Btn_grid_clicked()
{
    setAllGraphBtnsUnchecked();
    ui->Btn_grid->setChecked(true);
}

void HomePageWidget::on_Btn_list_clicked()
{
    setAllGraphBtnsUnchecked();
    ui->Btn_list->setChecked(true);
}
