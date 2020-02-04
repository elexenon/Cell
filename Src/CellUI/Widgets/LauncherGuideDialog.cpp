// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QVBoxLayout>

#include "ui_LauncherGuideDialog.h"
#include "LauncherGuideDialog.h"
#include "../CustomBaseWidgets/customTitleBar.h"
#include "../../CellCore/Kits/StyleSheetLoader.hpp"

LauncherGuideDialog::LauncherGuideDialog(QWidget *parent) :
    customWinstyleDialog(parent),
    mainLayout(new QVBoxLayout),
    ui(new Ui::LauncherGuideDialog),
    titleBar(new customTitleBar(this))
{
    ui->setupUi(this);
    Init();
}

LauncherGuideDialog::~LauncherGuideDialog()
{
    delete ui;
}

void LauncherGuideDialog::Init()
{
    customWinstyleDialog::LoadWinStyle(this);
    setLayout(mainLayout);
    setFixedHeight(533);

    mainLayout->setMargin(0);
    mainLayout->setSpacing(10);
    mainLayout->addWidget(titleBar);
    mainLayout->addWidget(ui->stackedWidget);

    QHBoxLayout *HLayout = new QHBoxLayout;
    HLayout->addWidget(ui->checkBox_showUp);
    HLayout->addStretch();
    HLayout->addWidget(ui->Btn_close);

    mainLayout->addLayout(HLayout);

    ui->stackedWidget->setAutoFillBackground(true);

    int fontIDInfo = QFontDatabase::addApplicationFont(CellUiConst::FONT_DIR + CHAR2STR("InfoDisplayWeb W01 Medium.ttf"));
    QFont fontInfo(QFontDatabase::applicationFontFamilies(fontIDInfo).at(0));

    titleBar->setFixedHeight(50);
    titleBar->setBrightDarkModeColor(CellUiConst::GRAYLEVEL255,CellUiConst::GRAYLEVEL45);
    titleBar->setText(CHAR2STR("CELL LAUNCHER"),CellUiConst::GRAYLEVEL130);
    titleBar->setFont(fontInfo, 23);
    titleBar->setIcon(CHAR2STR("CELL_logo_small"), 33, 29);
    titleBar->setLeftMargin(15);

    ui->checkBox_showUp->setFont(QFont(CHAR2STR("Microsoft YaHei UI Light")));
    ui->checkBox_showUp->setStyleSheet(CHAR2STR("QCheckBox{color:#798186;background-color: transparent;}"));

    CellEntityTools::styleSheetLoader->setStyleSheetName(CHAR2STR("LauncherGuideCloseBtn_Bright.css"));
    ui->Btn_close->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());
    ui->Btn_close->setFont(QFont(CHAR2STR("Microsoft YaHei UI")));
}

void LauncherGuideDialog::setColorScheme(CellUiGlobal::COLOR_SCHEME mode)
{
    if(m_mode == mode) return;
    m_mode = mode;
    //titleBar->setColorScheme(mode);
    if(mode == CellUiGlobal::COLOR_SCHEME::_DARK){
        CellEntityTools::styleSheetLoader->setStyleSheetName(CHAR2STR("LauncherGuideCloseBtn_Dark.css"));
        ui->Btn_close->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());
    }
    else{
        CellEntityTools::styleSheetLoader->setStyleSheetName(CHAR2STR("LauncherGuideCloseBtn_Bright.css"));
        ui->Btn_close->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());
    }
}

void LauncherGuideDialog::on_Btn_close_clicked()
{
    close();
}
static int cnt = 1;
void LauncherGuideDialog::on_pushButton_clicked()
{
    if(cnt == 3) cnt = 0;
    ui->stackedWidget->setCurrentIndex(cnt++);
}
