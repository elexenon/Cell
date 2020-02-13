// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "LauncherNewPJDialog.h"
#include "ui_launcherNewPJDialog.h"

#include "../CustomBaseWidgets/customTitleBar.h"
#include "../CustomBaseWidgets/customLabel.h"
#include "../CustomBaseWidgets/ButtonWithText.h"
#include "../CustomBaseWidgets/customListButton.h"
#include "../CustomBaseWidgets/customButtonListWidget.h"
#include "NewPJProjectCellPage.h"

#include <QStackedWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QTextStream>
#define DEBUG

LauncherNewPJDialog::LauncherNewPJDialog(CellUiGlobal::COLOR_SCHEME globalMode,QWidget *parent) :
    customWinstyleDialog(parent),
    ui(new Ui::LauncherNewPJDialog),
    titleBar(new customTitleBar(this)),
    label_choose(new customLabel(this)),
    btnConfirm(new ButtonWithText(customButton::DYNAMIC, this)),
    btnCancel(new ButtonWithText(customButton::DYNAMIC, this)),
    cellPage(new NewPJProjectCellPage),
    btnListWidget1(new customButtonListWidget(this)),
    btnListWidget2(new customButtonListWidget(this)),
    currEntity(new CellProjectEntity)
{
    ui->setupUi(this);
    Init();
    if(m_mode != globalMode)
        setColorScheme(globalMode);
}

LauncherNewPJDialog::~LauncherNewPJDialog()
{
    delete ui;
    delete currEntity;
}

void LauncherNewPJDialog::Init()
{
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    customWinstyleDialog::LoadWinStyle(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setBrightDarkModeColor(CellUiConst::GRAYLEVEL255, CellUiConst::GRAYLEVEL30);

    titleBar->setFixedHeight(40);
    titleBar->setBrightDarkModeColor(CellUiConst::GRAYLEVEL218, CellUiConst::GRAYLEVEL45);
    titleBar->setText(CHAR2STR("新建项目"), CellUiConst::GRAYLEVEL70);

    QFont font(CHAR2STR("Microsoft YaHei UI Light"));

    CellUiGlobal::setCustomTextLabel(label_choose, CHAR2STR("Microsoft YaHei UI Light"), 25, CHAR2STR("选择一个模板"));
    label_choose->setBrightDarkModeColor(CellUiConst::GRAYLEVEL70, CellUiConst::GRAYLEVEL255);

    btnListWidget1->addThemeHead(CHAR2STR("项目"));
    btnListWidget1->addButton(CHAR2STR("Cell DeepLearning"),CellUiConst::GRAYLEVEL247,CellUiConst::GRAYLEVEL70);
    btnListWidget1->addButton(CHAR2STR("地震预测系统"),CellUiConst::GRAYLEVEL247,CellUiConst::GRAYLEVEL70);
    btnListWidget1->setButtonsBrightDarkModeColor(CellUiConst::GRAYLEVEL255,CellUiConst::GRAYLEVEL30);
    btnListWidget1->setButtonSize(249,40);
    btnListWidget1->setSpacing(0);
    btnListWidget1->setBtnFontPixelSize(18);
    btnListWidget1->setBrightDarkModeColor(CellUiConst::GRAYLEVEL255,CellUiConst::GRAYLEVEL30);
    btnListWidget1->clickButton(0);

    btnListWidget2->addThemeHead(CHAR2STR("文件"));
    btnListWidget2->addButton(CHAR2STR("空白文件"),CellUiConst::GRAYLEVEL247,CellUiConst::GRAYLEVEL70);
    btnListWidget2->addButton(CHAR2STR("C++"),CellUiConst::GRAYLEVEL247,CellUiConst::GRAYLEVEL70);
    btnListWidget2->addButton(CHAR2STR("Python"),CellUiConst::GRAYLEVEL247,CellUiConst::GRAYLEVEL70);
    btnListWidget2->setButtonsBrightDarkModeColor(CellUiConst::GRAYLEVEL255,CellUiConst::GRAYLEVEL30);
    btnListWidget2->setButtonSize(249,40);
    btnListWidget2->setSpacing(0);
    btnListWidget2->setBtnFontPixelSize(18);
    btnListWidget2->setBrightDarkModeColor(CellUiConst::GRAYLEVEL255,CellUiConst::GRAYLEVEL30);

    btnConfirm->setBrightDarkModeColor(CellUiConst::GRAYLEVEL255, CellUiConst::GRAYLEVEL70);
    btnConfirm->setBrightModeHoveringColor(CellUiConst::GRAYLEVEL218);
    btnConfirm->setAnimationDuration(300);
    btnConfirm->init(CHAR2STR("确认"), 14);
    btnConfirm->setFixedSize(100, 27);
    btnConfirm->setCursor(Qt::PointingHandCursor);
    btnConfirm->setEnabled(false);

    btnCancel->setBrightDarkModeColor(CellUiConst::GRAYLEVEL255, CellUiConst::GRAYLEVEL70);
    btnCancel->setBrightModeHoveringColor(CellUiConst::GRAYLEVEL218);
    btnCancel->setAnimationDuration(300);
    btnCancel->init(CHAR2STR("取消"), 14);
    btnCancel->setFixedSize(100, 27);
    btnCancel->setCursor(Qt::PointingHandCursor);

    QHBoxLayout *HLayout_Bottom = new QHBoxLayout;
    HLayout_Bottom->addWidget(btnConfirm);
    HLayout_Bottom->addWidget(btnCancel);
    HLayout_Bottom->setSpacing(17);
    HLayout_Bottom->setMargin(0);

    QHBoxLayout *HLayout_Top = new QHBoxLayout;
    HLayout_Top->addWidget(label_choose);
    HLayout_Top->setAlignment(Qt::AlignmentFlag::AlignHCenter);

    QVBoxLayout *VLayout_left = new QVBoxLayout;
    VLayout_left->addLayout(HLayout_Top);
    VLayout_left->addStretch();
    VLayout_left->addWidget(btnListWidget1);
    VLayout_left->addWidget(btnListWidget2);
    VLayout_left->addStretch();
    VLayout_left->addLayout(HLayout_Bottom);
    VLayout_left->setContentsMargins(0, 20, 0, 11);
    VLayout_left->setSpacing(20);

    VLineSplitter = CellUiGlobal::getLine(CellUiGlobal::LINE_TYPE::VLine);

    QHBoxLayout *HLayout = new QHBoxLayout;
    HLayout->addLayout(VLayout_left);
    HLayout->addWidget(VLineSplitter);
    HLayout->addWidget(ui->stackedWidget);
    HLayout->setMargin(0);
    HLayout->setSpacing(0);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(titleBar);
    mainLayout->addLayout(HLayout);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    setLayout(mainLayout);

    ui->stackedWidget->insertWidget(1, cellPage);
    ui->stackedWidget->setCurrentIndex(1);

    setEventConnections();
}

void LauncherNewPJDialog::setEventConnections()
{
    connect(btnListWidget1, SIGNAL(clicked(int)), this, SLOT(btnListWidget1Clicked(int)));
    connect(btnListWidget2, SIGNAL(clicked(int)), this, SLOT(btnListWidget2Clicked(int)));

    connect(cellPage, &NewPJProjectCellPage::pathSettled, this, &LauncherNewPJDialog::setPath);
    connect(cellPage, &NewPJProjectCellPage::nameSettled, this, &LauncherNewPJDialog::setName);

    connect(btnCancel, &QPushButton::clicked, this, &LauncherNewPJDialog::btnCancelClicked);
    connect(btnConfirm, &QPushButton::clicked, this, &LauncherNewPJDialog::btnConfirmClicked);
}

void LauncherNewPJDialog::setColorScheme(CellUiGlobal::COLOR_SCHEME mode){
    if(mode == m_mode) return;
    emit enableColorScheme(mode);
    customWinstyleDialog::setColorScheme(mode);
}

void LauncherNewPJDialog::btnListWidget1Clicked(int id)
{
#ifdef DEBUG
    qDebug() << "btnListWidget1 Clicked::Tab::" << id;
#endif
    btnListWidget1->setExlusive(true);
    btnListWidget2->setExlusive(false);
    auto list = btnListWidget2->getButtons();
    for(auto & e : *list)
        e->setChecked(false);

    switch(id){
    case 0:
        currEntity->setType(CellProjectEntity::_CELLDEEPLEARNING);
        break;
    case 1:
        currEntity->setType(CellProjectEntity::_PREDICTEARTHQUAKE);
        break;
    }
}

void LauncherNewPJDialog::btnListWidget2Clicked(int id)
{
#ifdef DEBUG
    qDebug() << "btnListWidget2 Clicked::Tab::" << id;
#endif
    btnListWidget2->setExlusive(true);
    btnListWidget1->setExlusive(false);
    auto list = btnListWidget1->getButtons();
    for(auto & e : *list)
        e->setChecked(false);

    switch(id){
    case 0:
        currEntity->setType(CellProjectEntity::_EMPTY);
        break;
    case 1:
        currEntity->setType(CellProjectEntity::_CPP);
        break;
    case 2:
        currEntity->setType(CellProjectEntity::_PYTHON);
        break;
    }
}

void LauncherNewPJDialog::setName(const QString &name)
{
    currEntity->setName(name);
    judgeValidProject();
}

void LauncherNewPJDialog::setPath(const QString &path)
{
    currEntity->setPath(path);
    judgeValidProject();
}

void LauncherNewPJDialog::btnConfirmClicked()
{
    emit projectSettled(*currEntity);
    this->close();
}

void LauncherNewPJDialog::judgeValidProject()
{
    if(currEntity->name() != CMPSTR("") && currEntity->path() != CMPSTR(""))
        btnConfirm->setEnabled(true);
    else
        btnConfirm->setEnabled(false);
}
