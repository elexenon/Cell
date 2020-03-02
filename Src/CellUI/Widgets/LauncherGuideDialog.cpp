// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QCheckBox>
#include <QLabel>

#include "LauncherGuideDialog.h"
#include "../CustomBaseWidgets/ButtonWithIcon.h"
#include "../CustomBaseWidgets/ButtonWithText.h"
#include "../CustomBaseWidgets/customFrame.h"
#include "../CustomBaseWidgets/customLabel.h"
#include "../CustomBaseWidgets/customTitleBar.h"
#include "../CustomBaseWidgets/customStackedWidget.h"
#include "../../CellCore/CellNamespace.h"

LauncherGuideDialog::LauncherGuideDialog(QWidget *parent) :
    customWinstyleDialog(parent),
    mainLayout(new QVBoxLayout(this)),
    titleBar(new customTitleBar(this)),
    mainStackedWidget(new customStackedWidget(this)),
    bottomBar(new customFrame(customFrame::_REGULAR, this)),
    checkBox(new QCheckBox(bottomBar)),
    btnClose(new ButtonWithText(customButton::DYNAMIC, bottomBar)),
    btnNewPJ(new ButtonWithText(customButton::DYNAMIC, bottomBar))
{
    init();
    setEventConnections();
}

void LauncherGuideDialog::init()
{
    customWinstyleDialog::LoadWinStyle(this);
    setLayout(mainLayout);
    setFixedSize(920, 580);

    // TitleBar Combination.
    titleBar->setFixedHeight(40);
    titleBar->setBrightDarkModeColor(Cell::CGL218,Cell::CGL45);
    titleBar->setText("");
    titleBar->setFont(CellUiGlobal::getFont(CHAR2STR("InfoDisplayWeb W01 Medium.ttf"), 21));
    titleBar->setIcon(CHAR2STR("cellLogo28"), 0, 0);
    titleBar->setLeftMargin(15);

    // BottomBar Combination.
    checkBox->setChecked(true);
    checkBox->setText(CHAR2STR("启动时显示此面板"));
    checkBox->setFont(CellUiGlobal::getFont(CHAR2STR("Microsoft YaHei UI"), 13));
    checkBox->setStyleSheet(CHAR2STR("QCheckBox{color:white;background-color: transparent;}"));

    btnClose->setBrightDarkModeColor(Cell::CGL70, Cell::CGL70);
    btnClose->setBrightModeHoveringColor(Cell::NavyBlue);
    btnClose->setDarkModeHoveringColor(Cell::NavyBlue);
    btnClose->setAnimationDuration(200);
    btnClose->init(CHAR2STR("关闭"), 15);
    btnClose->setTextColor(Cell::CGL255, Cell::CGL255);
    btnClose->setFixedSize(100, 40);

    btnNewPJ->setBrightDarkModeColor(Cell::CGL100, Cell::CGL100);
    btnNewPJ->setBrightModeHoveringColor(Cell::NavyBlue);
    btnNewPJ->setDarkModeHoveringColor(Cell::NavyBlue);
    btnNewPJ->setAnimationDuration(200);
    btnNewPJ->init(CHAR2STR("新建文档"), 15);
    btnNewPJ->setTextColor(Cell::CGL255, Cell::CGL255);
    btnNewPJ->setFixedSize(100, 40);

    QHBoxLayout *HLayoutBottom = new QHBoxLayout(bottomBar);
    HLayoutBottom->setContentsMargins(15, 0, 0, 0);
    HLayoutBottom->setSpacing(0);
    HLayoutBottom->addWidget(checkBox);
    HLayoutBottom->addStretch();
    HLayoutBottom->addWidget(btnClose);
    HLayoutBottom->addWidget(btnNewPJ);

    bottomBar->setBrightDarkModeColor(Cell::CGL60, Cell::CGL60);
    bottomBar->setFixedHeight(40);

    customFrame *f1 = new customFrame(customFrame::_REGULAR, this);
    f1->setBrightDarkModeColor(Cell::CGL247, Cell::CGL60);

    customFrame *f2 = new customFrame(customFrame::_REGULAR, this);
    f2->setBrightDarkModeColor(Cell::CGL130, Cell::CGL60);

    mainStackedWidget->setAnimiDuration(800);
    mainStackedWidget->insertWidget(0, f1);
    mainStackedWidget->insertWidget(1, f2);


    // Set MainLayout
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(titleBar);
    mainLayout->addWidget(mainStackedWidget);
    mainLayout->addWidget(bottomBar);
}

void LauncherGuideDialog::fade()
{
    animi = new QPropertyAnimation;
    connect(animi, &QPropertyAnimation::finished, this, &LauncherGuideDialog::close);

    animi->setTargetObject(this);
    animi->setPropertyName("windowOpacity");
    animi->setEasingCurve(QEasingCurve::Linear);
    animi->setDuration(150);
    animi->setStartValue(1);
    animi->setEndValue(0);
    animi->start(QAbstractAnimation::DeleteWhenStopped);
}

void LauncherGuideDialog::setEventConnections()
{
    connect(btnClose, &QPushButton::clicked, this, &LauncherGuideDialog::fade);
    connect(btnNewPJ, &QPushButton::clicked, this, &LauncherGuideDialog::btnNewPJClicked);
}

void LauncherGuideDialog::showEvent(QShowEvent *e)
{
    (void)e;
    this->setWindowOpacity(1);
}

void LauncherGuideDialog::setColorScheme(Cell::ColorScheme mode)
{
    customWinstyleDialog::setColorScheme(mode);
}
