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
    bottomBar(new customFrame(customFrame::Type::Regular, this)),
    checkBox(new QCheckBox(bottomBar)),
    btnClose(new ButtonWithText(customButton::Dynamic, bottomBar)),
    btnNewPJ(new ButtonWithText(customButton::Dynamic, bottomBar))
{
    init();
    setEventConnections();
}

void LauncherGuideDialog::init()
{
    customWinstyleDialog::LoadWinStyle(this);
    setWindowTitle(CHAR2STR("Guide"));
    setModal(true);
    setLayout(mainLayout);
    setAttribute(Qt::WA_DeleteOnClose);
    setFixedSize(920, 580);
    // TitleBar Combination.
    titleBar->setFixedHeight(40);
    titleBar->setBrightDarkColor(Cell::CGL218,Cell::CGL60);
    titleBar->setText("");
    titleBar->setFont(CellUiGlobal::getFont(CHAR2STR("InfoDisplayWeb W01 Medium.ttf"), 21));
    titleBar->setIcon(CHAR2STR("cellLogo28"), 0, 0);
    titleBar->setLeftMargin(15);

    // BottomBar Combination.
    checkBox->setChecked(true);
    checkBox->setText(CHAR2STR("启动时显示此面板"));
    checkBox->setFont(CellUiGlobal::getFont(CHAR2STR("Microsoft YaHei UI"), 13));
    checkBox->setStyleSheet(CHAR2STR("QCheckBox{color:white;background-color: transparent;}"));

    btnClose->setBrightDarkColor(Cell::CGL70, Cell::CGL70);
    btnClose->setBrightHoveringColor(Cell::CellThemeColor::ExitRed);
    btnClose->setDarkHoveringColor(Cell::CellThemeColor::ExitRed);
    btnClose->setAnimationDuration(200);
    btnClose->initModules(CHAR2STR("关闭"), 15);
    btnClose->setTextColor(Cell::CGL255, Cell::CGL255);
    btnClose->setFixedSize(100, 40);

    btnNewPJ->setBrightDarkColor(Cell::CGL100, Cell::CGL100);
    btnNewPJ->setBrightHoveringColor(Cell::CellThemeColor::NavyBlue);
    btnNewPJ->setDarkHoveringColor(Cell::CellThemeColor::NavyBlue);
    btnNewPJ->setAnimationDuration(200);
    btnNewPJ->initModules(CHAR2STR("新建文档"), 15);
    btnNewPJ->setTextColor(Cell::CGL255, Cell::CGL255);
    btnNewPJ->setFixedSize(100, 40);

    QHBoxLayout *HLayoutBottom = new QHBoxLayout(bottomBar);
    HLayoutBottom->setContentsMargins(15, 0, 0, 0);
    HLayoutBottom->setSpacing(0);
    HLayoutBottom->addWidget(checkBox);
    HLayoutBottom->addStretch();
    HLayoutBottom->addWidget(btnClose);
    HLayoutBottom->addWidget(btnNewPJ);

    bottomBar->setBrightDarkColor(Cell::CGL60, Cell::CGL60);
    bottomBar->setFixedHeight(40);

    customFrame *f1 = new customFrame(customFrame::Type::Regular, this);
    f1->setBrightDarkColor(Cell::CGL247, Cell::CGL60);

    customFrame *f2 = new customFrame(customFrame::Type::Regular, this);
    f2->setBrightDarkColor(Cell::CGL130, Cell::CGL60);

    mainStackedWidget->setAnimiDuration(800);
    mainStackedWidget->insertWidget(0, f1);
    mainStackedWidget->insertWidget(1, f2);

    _modules << titleBar << btnClose << btnNewPJ << bottomBar;


    // Set MainLayout
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(titleBar);
    mainLayout->addWidget(mainStackedWidget);
    mainLayout->addWidget(bottomBar);
}

void LauncherGuideDialog::fade()
{
    animiPtr = new QPropertyAnimation;
    connect(animiPtr, &QPropertyAnimation::finished, this, &LauncherGuideDialog::close);

    animiPtr->setTargetObject(this);
    animiPtr->setPropertyName("windowOpacity");
    animiPtr->setEasingCurve(QEasingCurve::Linear);
    animiPtr->setDuration(150);
    animiPtr->setStartValue(1);
    animiPtr->setEndValue(0);
    animiPtr->start(QAbstractAnimation::DeleteWhenStopped);  
}

void LauncherGuideDialog::setEventConnections()
{
    connect(btnClose, &QPushButton::clicked, this, [=]{
        onCloseNewPJ = false; fade();
    });
    connect(btnNewPJ, &QPushButton::clicked, this, [=]{
        onCloseNewPJ = true; fade();
    });
    connect(checkBox, &QCheckBox::clicked, this, &LauncherGuideDialog::checkBoxClicked);
}

void LauncherGuideDialog::showEvent(QShowEvent *e){
    this->setWindowOpacity(1);
    e->accept();
}

void LauncherGuideDialog::closeEvent(QCloseEvent *e){
    if(onCloseNewPJ) emit clickedNewPJ();
    e->accept();
}

void LauncherGuideDialog::setCheckBox(bool checked){
    checkBox->setChecked(checked);
}
