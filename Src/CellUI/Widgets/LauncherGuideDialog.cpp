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

    ui->stackedWidget->setAutoFillBackground(true);

    ui->pushButton->setParent(this);
    ui->pushButton->setGeometry(640, 420, ui->pushButton->width(), ui->pushButton->height());

    int fontIDInfo = QFontDatabase::addApplicationFont(CellUiConst::FONT_DIR + QStringLiteral("InfoDisplayWeb W01 Medium.ttf"));
    QFont fontInfo(QFontDatabase::applicationFontFamilies(fontIDInfo).at(0));

    titleBar->setFixedHeight(55);
    titleBar->setBrightDarkModeColor(CellUiConst::GRAYLEVEL255,CellUiConst::GRAYLEVEL45);
    titleBar->setText(QString::fromUtf8("CELL LAUNCHER"),CellUiConst::GRAYLEVEL130);
    titleBar->setFont(fontInfo, 23);
    titleBar->setIcon(QString::fromUtf8("CELL_logo_small"), 33, 29);
    titleBar->setLeftMargin(15);

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
    //titleBar->setColorScheme(mode);
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
