// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include <QPropertyAnimation>
#include <QMouseEvent>
#include "ui_LauncherGuideDialog.h"
#include "LauncherGuideDialog.h"
#include "../CustomBaseWidgets/customFrame.h"
#include "../../CellCore/Kits/StyleSheetLoader.hpp"

LauncherGuideDialog::LauncherGuideDialog(QWidget *parent) :
    customWinstyleDialog(parent),
    ui(new Ui::LauncherGuideDialog),
    frame_titleBar(new customFrame(CellUiConst::QSS_CUSTOMFRAME, this))
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

    ui->stackedWidget->setAutoFillBackground(true);

    ui->pushButton->setParent(this);
    ui->pushButton->setGeometry(640, 420, ui->pushButton->width(), ui->pushButton->height());

    frame_titleBar->setGeometry(0, 0, 781, 51);
    frame_titleBar->setBrightDarkModeColor(CellUiConst::GRAYLEVEL218, CellUiConst::GRAYLEVEL45);

    ui->label_getStart->setFont(QFont(QStringLiteral("Microsoft YaHei UI"), 18));
    ui->label_learn->setFont(QFont(QStringLiteral("Microsoft YaHei UI"), 9));
    CellUiGlobal::multiModulesOneStyleSheet({ui->label_getStart,ui->label_learn},QStringLiteral("QLabel{color:#DCDCDC;background-color: transparent;}"));

    ui->checkBox_showUp->setFont(QFont(QStringLiteral("Microsoft YaHei UI Light")));
    ui->checkBox_showUp->setStyleSheet(QStringLiteral("QCheckBox{color:#798186;background-color: transparent;}"));

    CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("LauncherGuideCloseBtn_Bright.css"));
    ui->Btn_close->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());
    ui->Btn_close->setFont(QFont(QStringLiteral("Microsoft YaHei UI")));
}

void LauncherGuideDialog::setColorScheme(CellUiGlobal::COLOR_SCHEME mode)
{
    if(m_mode == mode) return;
    m_mode = mode;
    frame_titleBar->setColorScheme(mode);
    if(mode == CellUiGlobal::COLOR_SCHEME::_DARK){
        CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("LauncherGuideCloseBtn_Dark.css"));
        ui->Btn_close->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());
    }
    else{
        CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("LauncherGuideCloseBtn_Bright.css"));
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
