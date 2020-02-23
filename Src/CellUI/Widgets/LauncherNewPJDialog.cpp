// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "LauncherNewPJDialog.h"

#include "../../CellCore/CellNamespace.h"
#include "../CustomBaseWidgets/customTitleBar.h"
#include "../CustomBaseWidgets/customLabel.h"
#include "../CustomBaseWidgets/ButtonWithText.h"
#include "../CustomBaseWidgets/customListButton.h"
#include "../CustomBaseWidgets/customButtonListWidget.h"
#include "NewPJProjectCellPage.h"
#include "NewPJPredictEarPage.h"

#include <QStackedWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QTextStream>
#define DEBUG

LauncherNewPJDialog::LauncherNewPJDialog(CellUiGlobal::COLOR_SCHEME globalMode,QWidget *parent) :
    customWinstyleDialog(parent),
    titleBar(new customTitleBar(this)),
    label_choose(new customLabel(this)),
    btnConfirm(new ButtonWithText(customButton::DYNAMIC, this)),
    btnCancel(new ButtonWithText(customButton::DYNAMIC, this)),
    stackedWidget(new QStackedWidget(this)),
    cellPage(new NewPJProjectCellPage(this)),
    prePage(new NewPJPredictEarPage(this)),
    btnListWidget1(new customButtonListWidget(this)),
    btnListWidget2(new customButtonListWidget(this)),
    currEntity(new CellProjectEntity)
{
    init();
    if(m_mode != globalMode)
        setColorScheme(globalMode);
    setEventConnections();
}

LauncherNewPJDialog::~LauncherNewPJDialog()
{
    SafeDelete(currEntity);
}

void LauncherNewPJDialog::init()
{
    customWinstyleDialog::LoadWinStyle(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setBrightDarkModeColor(Cell::CGL255, Cell::CGL30);
    resize(900, 520);

    titleBar->setFixedHeight(40);
    titleBar->setBrightDarkModeColor(Cell::CGL218, Cell::CGL45);
    titleBar->setText(CHAR2STR("新建项目"), Cell::CGL70);

    QFont font(CHAR2STR("Microsoft YaHei UI Light"));

    CellUiGlobal::setCustomTextLabel(label_choose, CHAR2STR("Microsoft YaHei UI Light"), 25, CHAR2STR("选择一个模板"));
    label_choose->setBrightDarkModeColor(Cell::CGL70, Cell::CGL255);

    btnListWidget1->addThemeHead(CHAR2STR("项目"));
    btnListWidget1->addButton(CHAR2STR("Cell DeepLearning"),Cell::CGL247,Cell::CGL70);
    btnListWidget1->addButton(CHAR2STR("地震预测系统"),Cell::CGL247,Cell::CGL70);
    btnListWidget1->setButtonsBrightDarkModeColor(Cell::CGL255,Cell::CGL30);
    btnListWidget1->setButtonSize(249,40);
    btnListWidget1->setSpacing(0);
    btnListWidget1->setBtnFontPixelSize(18);
    btnListWidget1->setBrightDarkModeColor(Cell::CGL255,Cell::CGL30);
    btnListWidget1->clickButton(0);

    btnListWidget2->addThemeHead(CHAR2STR("文件"));
    btnListWidget2->addButton(CHAR2STR("空白文件"),Cell::CGL247,Cell::CGL70);
    btnListWidget2->addButton(CHAR2STR("C++"),Cell::CGL247,Cell::CGL70);
    btnListWidget2->addButton(CHAR2STR("Python"),Cell::CGL247,Cell::CGL70);
    btnListWidget2->setButtonsBrightDarkModeColor(Cell::CGL255,Cell::CGL30);
    btnListWidget2->setButtonSize(249,40);
    btnListWidget2->setSpacing(0);
    btnListWidget2->setBtnFontPixelSize(18);
    btnListWidget2->setBrightDarkModeColor(Cell::CGL255,Cell::CGL30);

    btnConfirm->setBrightDarkModeColor(Cell::CGL255, Cell::CGL70);
    btnConfirm->setBrightModeHoveringColor(Cell::CGL218);
    btnConfirm->setAnimationDuration(300);
    btnConfirm->init(CHAR2STR("确认"), 14);
    btnConfirm->setFixedSize(100, 27);
    btnConfirm->setCursor(Qt::PointingHandCursor);
    btnConfirm->setEnabled(false);

    btnCancel->setBrightDarkModeColor(Cell::CGL255, Cell::CGL70);
    btnCancel->setBrightModeHoveringColor(Cell::CGL218);
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

    QHBoxLayout *HLayout = new QHBoxLayout;
    HLayout->addLayout(VLayout_left);
    HLayout->addWidget(CellUiGlobal::getLine(CellUiGlobal::LINE_TYPE::VLine));
    HLayout->addWidget(stackedWidget);
    HLayout->setMargin(0);
    HLayout->setSpacing(0);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(titleBar);
    mainLayout->addLayout(HLayout);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    setLayout(mainLayout);

    // Stacked Widget Combination.
    newPJPageBase *emptyPJPage = new newPJPageBase(stackedWidget);
    emptyPJPage->setPageTitle(CHAR2STR("空文本文件。"));

    newPJPageBase *cppPJPage = new newPJPageBase(stackedWidget);
    cppPJPage->setPageTitle(CHAR2STR("Pure C++ File"));

    newPJPageBase *pyPJPage = new newPJPageBase(stackedWidget);
    pyPJPage->setPageTitle(CHAR2STR("Pure Python File"));

    QList<newPJPageBase*> pages;
    pages.append(cellPage);
    pages.append(prePage);
    pages.append(emptyPJPage);
    pages.append(cppPJPage);
    pages.append(pyPJPage);

    int index = 0;
    for(auto & e : pages)
        stackedWidget->insertWidget(index++, e);
}

void LauncherNewPJDialog::setEventConnections()
{
    connect(btnListWidget1, &customButtonListWidget::clicked, this, &LauncherNewPJDialog::btnListWidget1Clicked);
    connect(btnListWidget2, &customButtonListWidget::clicked, this, &LauncherNewPJDialog::btnListWidget2Clicked);

    connect(cellPage, &newPJPageBase::pathSettled, this, &LauncherNewPJDialog::setPath);
    connect(cellPage, &newPJPageBase::nameSettled, this, &LauncherNewPJDialog::setName);

    connect(prePage, &newPJPageBase::pathSettled, this, &LauncherNewPJDialog::setPath);
    connect(prePage, &newPJPageBase::nameSettled, this, &LauncherNewPJDialog::setName);

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
        currEntity->setType(CellProjectEntity::CellDeepLearning);
        stackedWidget->setCurrentIndex(0);
        break;
    case 1:
        currEntity->setType(CellProjectEntity::PredictEarthquake);
        stackedWidget->setCurrentIndex(1);
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
        currEntity->setType(CellProjectEntity::Empty);
        stackedWidget->setCurrentIndex(2);
        break;
    case 1:
        currEntity->setType(CellProjectEntity::CPP);
        stackedWidget->setCurrentIndex(3);
        break;
    case 2:
        currEntity->setType(CellProjectEntity::Python);
        stackedWidget->setCurrentIndex(4);
        break;
    }
}

void LauncherNewPJDialog::setName(const QString &name)
{
    QRegExp exp(CHAR2STR("[<>\"?/\\\\|:*]"));
    if(name.indexOf(exp) >= 0)
        currEntity->setName(CHAR2STR(""));
    else
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
    emit projectSettled(currEntity);
    this->close();
}

void LauncherNewPJDialog::judgeValidProject()
{
    if(currEntity->name() != CMPSTR("") && currEntity->path() != CMPSTR(""))
        btnConfirm->setEnabled(true);
    else
        btnConfirm->setEnabled(false);
}
