// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
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
#include "../CustomBaseWidgets/customStackedWidget.h"
#include "../../CellCore/Kits/StyleSheetLoader.hpp"

LauncherGuideDialog::LauncherGuideDialog(QWidget *parent) :
    customWinstyleDialog(parent),
    mainLayout(new QVBoxLayout(this)),
    titleBar(new customFrame(customFrame::_REGULAR, this)),
    icon(new QLabel(titleBar)),
    labelTitle(new customLabel(titleBar)),
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
    setFixedSize(950, 620);

    // TitleBar Combination.
    CellUiGlobal::setLabelPixmap(icon, CHAR2STR("cellLogo128"), 50, 50);

    labelTitle->setBrightDarkModeColor(CellUiConst::GRAYLEVEL255, CellUiConst::GRAYLEVEL255);
    CellUiGlobal::setCustomTextLabel(labelTitle, CHAR2STR("Microsoft YaHei UI"), 23, CHAR2STR("CELL深度学习向导。"));

    QHBoxLayout *HLayoutTitleBar = new QHBoxLayout(titleBar);
    HLayoutTitleBar->setContentsMargins(15, 0, 0, 0);
    HLayoutTitleBar->setSpacing(10);
    HLayoutTitleBar->setAlignment(Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
    HLayoutTitleBar->addWidget(icon);
    HLayoutTitleBar->addWidget(labelTitle);

    titleBar->setBrightDarkModeColor(CellUiConst::GRAYLEVEL60, CellUiConst::GRAYLEVEL60);
    titleBar->setFixedHeight(75);
    titleBar->setLayout(HLayoutTitleBar);

    // BottomBar Combination.
    checkBox->setChecked(true);
    checkBox->setText(CHAR2STR("启动时显示此面板"));
    checkBox->setFont(CellUiGlobal::getFont(CHAR2STR("Microsoft YaHei UI"), 13));
    checkBox->setStyleSheet(CHAR2STR("QCheckBox{color:white;background-color: transparent;}"));

    btnClose->setBrightDarkModeColor(CellUiConst::GRAYLEVEL70, CellUiConst::GRAYLEVEL70);
    btnClose->setBrightModeHoveringColor(CellUiConst::CELLTHEMECOLOR);
    btnClose->setDarkModeHoveringColor(CellUiConst::CELLTHEMECOLOR);
    btnClose->setAnimationDuration(200);
    btnClose->init(CHAR2STR("关闭"), 15);
    btnClose->setTextColor(CellUiConst::GRAYLEVEL255, CellUiConst::GRAYLEVEL255);
    btnClose->setFixedSize(100, 40);

    btnNewPJ->setBrightDarkModeColor(CellUiConst::GRAYLEVEL100, CellUiConst::GRAYLEVEL100);
    btnNewPJ->setBrightModeHoveringColor(CellUiConst::CELLTHEMECOLOR);
    btnNewPJ->setDarkModeHoveringColor(CellUiConst::CELLTHEMECOLOR);
    btnNewPJ->setAnimationDuration(200);
    btnNewPJ->init(CHAR2STR("新建文档"), 15);
    btnNewPJ->setTextColor(CellUiConst::GRAYLEVEL255, CellUiConst::GRAYLEVEL255);
    btnNewPJ->setFixedSize(100, 40);

    QHBoxLayout *HLayoutBottom = new QHBoxLayout(bottomBar);
    HLayoutBottom->setContentsMargins(15, 0, 0, 0);
    HLayoutBottom->setSpacing(0);
    HLayoutBottom->addWidget(checkBox);
    HLayoutBottom->addStretch();
    HLayoutBottom->addWidget(btnClose);
    HLayoutBottom->addWidget(btnNewPJ);

    bottomBar->setBrightDarkModeColor(CellUiConst::GRAYLEVEL60, CellUiConst::GRAYLEVEL60);
    bottomBar->setFixedHeight(40);

    customFrame *f1 = new customFrame(customFrame::_REGULAR, this);
    f1->setBrightDarkModeColor(CellUiConst::GRAYLEVEL30, CellUiConst::GRAYLEVEL60);

    customFrame *f2 = new customFrame(customFrame::_REGULAR, this);
    f2->setBrightDarkModeColor(CellUiConst::GRAYLEVEL130, CellUiConst::GRAYLEVEL60);

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

void LauncherGuideDialog::setEventConnections()
{
    connect(btnClose, &QPushButton::clicked, this, &LauncherGuideDialog::btnCloseClicked);
    connect(btnNewPJ, &QPushButton::clicked, this, &LauncherGuideDialog::btnNewPJClicked);
}

void LauncherGuideDialog::setColorScheme(CellUiGlobal::COLOR_SCHEME mode)
{
    (void)mode;
}
