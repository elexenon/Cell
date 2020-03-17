// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QFontDatabase>
#include <QDebug>
#include <QTime>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QStackedWidget>

#include "LauncherGuideDialog.h"
#include "LauncherNewPJDialog.h"
#include "LauncherNewPJGUI.h"
#include "LauncherHomepage.h"
#include "LauncherSettings.h"
#include "WorkShop.h"
#include "DeepSense.h"
#include "Launcher.h"

#include "../../../CellDevelopTestStation.h"
#include "../../CellCore/CellNamespace.h"
#include "../../CellCore/Kits/CellGlobalMacros.h"
#include "../CustomBaseWidgets/customListButton.h"
#include "../CustomBaseWidgets/ButtonWithIconTextHint.h"
#include "../CustomBaseWidgets/customButtonListWidget.h"
#include "../CustomBaseWidgets/customNotificationCenter.h"
#include "../CustomBaseWidgets/customTitleBar.h"
#include "../CustomBaseWidgets/customDialogButton.h"
#include "../CustomBaseWidgets/ButtonWithIcon.h"

#define ENABLE_WORKSHOP
//#define RELEASE_MODE

Launcher::Launcher(QWidget *parent)
    : customWinstyleWidget(parent),
      mainLayout(new QVBoxLayout(this)),
      homePage(new LauncherHomepage(this)),
      settingsPage(new LauncherSettings(this)),
      titleBar(new customTitleBar(this)),
      btnMini(new ButtonWithIcon(customButton::Dynamic, titleBar)),
      btnMax(new ButtonWithIcon(customButton::Dynamic, titleBar)),
      btnClose(new ButtonWithIcon(customButton::Dynamic, titleBar)),
      stackedWidget(new QStackedWidget(this)),
      btnNewCode(new ButtonWithIconTextHint(customButton::Dynamic | customButton::Radius, this)),
      btnNewGUI(new ButtonWithIconTextHint(customButton::Dynamic | customButton::Radius, this)),
      btnOpen(new ButtonWithIconTextHint(customButton::Dynamic | customButton::Radius, this)),
      notificationCenter(new class notificationCenter(this)),
      btnListWidget(new customButtonListWidget(this)),
#ifndef RELEASE_MODE
      testForm(new CellDevelopTestStation(this)),
#endif
      currentPage(PAGE_TYPE::_HOME)
{
    init();
    setEventConnections();
}

const QRect Launcher::maskGeometry(){
    return QRect(0, titleBar->height(), this->width(),this->height()-titleBar->height()-notificationCenter->height());
}

void Launcher::init(){
    resize(1400, 800);
    setObjectName(CHAR2STR("Launcher"));
    customWinstyleWidget::LoadWinStyle(this);
    setBrightDarkColor(Cell::CGL247, Cell::CGL30);

    // Set Title Bar.
    QHBoxLayout *HLayoutTitleRight = new QHBoxLayout;
    HLayoutTitleRight->setSpacing(0);
    HLayoutTitleRight->addWidget(btnMini);
    HLayoutTitleRight->addWidget(btnMax);
    HLayoutTitleRight->addWidget(btnClose);
    HLayoutTitleRight->setContentsMargins(0, 0, 0, 0);

    titleBar->setFixedHeight(40);
    titleBar->setBrightDarkColor(Cell::CGL255,Cell::CGL45);
    titleBar->setText(CHAR2STR("CELL LAUNCHER"),Cell::CGL130);
    titleBar->setFont(CellUiGlobal::getFont(CHAR2STR("InfoDisplayWeb W01 Medium.ttf"), 21));
    titleBar->setIcon(CHAR2STR("cellLogo28"), 28, 28);
    titleBar->setLeftMargin(15);
    titleBar->addLayout(HLayoutTitleRight);

    btnMini->setBrightHoveringColor(Cell::CellThemeColor::NavyBlue);
    btnMini->setDarkHoveringColor(Cell::CellThemeColor::NavyBlue);
    btnMini->setBrightDarkColor(Cell::CGL255, Cell::CGL45);
    btnMini->setAnimationDuration(150);
    btnMini->initModules(CHAR2STR("iconMinimize"), 15, 2);
    btnMini->setFixedSize(50, titleBar->height());

    btnMax->setBrightHoveringColor(Cell::CellThemeColor::NavyBlue);
    btnMax->setDarkHoveringColor(Cell::CellThemeColor::NavyBlue);
    btnMax->setBrightDarkColor(Cell::CGL255, Cell::CGL45);
    btnMax->setAnimationDuration(150);
    btnMax->initModules(CHAR2STR("iconMaximize"), 17, 14);
    btnMax->setFixedSize(50, titleBar->height());

    btnClose->setBrightHoveringColor(Cell::CellThemeColor::ExitRed);
    btnClose->setDarkHoveringColor(Cell::CellThemeColor::ExitRed);
    btnClose->setBrightDarkColor(Cell::CGL255, Cell::CGL45);
    btnClose->setAnimationDuration(150);
    btnClose->initModules(CHAR2STR("iconClose"), 14, 14);
    btnClose->setFixedSize(50, titleBar->height());

    // Set HLayout
    // Set Left Layout.
    // Set Button List Widget.
    btnListWidget->addButton(CHAR2STR("主页"),Cell::CGL218,Cell::CGL70);
    btnListWidget->addButton(CHAR2STR("选项"),Cell::CGL218,Cell::CGL70);
    btnListWidget->addButton(CHAR2STR("向导"),Cell::CGL218,Cell::CGL70);
    btnListWidget->setButtonCheckable(2,false);
#ifndef RELEASE_MODE
    btnListWidget->addButton(CHAR2STR("自定义CONTROLS测试面板"),Cell::CGL218,Cell::CGL70);
    btnListWidget->setButtonCheckable(3,false);
#endif
    btnListWidget->setButtonsBrightDarkModeColor(Cell::CGL247,Cell::CGL30);
    btnListWidget->setButtonSize(251,31);
    btnListWidget->setBrightDarkColor(Cell::CGL247,Cell::CGL30);
    btnListWidget->clickButton(0);

    // Set Work Buttons.
    btnNewCode->setBrightHoveringColor(Cell::CGL255);
    btnNewCode->setDarkHoveringColor(Cell::CGL130);
    btnNewCode->setBrightDarkColor(Cell::CGL218, Cell::CGL70);
    btnNewCode->setAnimationDuration(200);
    btnNewCode->initModules(CHAR2STR("iconNewCode"), 33, 33, CHAR2STR("代码项目"), 25, CHAR2STR("新的纯代码Cell项目"));
    btnNewCode->setFixedSize(250, 81);

    btnNewGUI->setBrightHoveringColor(Cell::CGL255);
    btnNewGUI->setDarkHoveringColor(Cell::CGL130);
    btnNewGUI->setBrightDarkColor(Cell::CGL218, Cell::CGL70);
    btnNewGUI->setAnimationDuration(200);
    btnNewGUI->initModules(CHAR2STR("iconNewGUI"), 33, 33, CHAR2STR("引导项目"), 25, CHAR2STR("新的图形化Cell项目"));
    btnNewGUI->setFixedSize(250, 81);

    btnOpen->setBrightHoveringColor(Cell::CGL255);
    btnOpen->setDarkHoveringColor(Cell::CGL130);
    btnOpen->setBrightDarkColor(Cell::CGL218, Cell::CGL70);
    btnOpen->setAnimationDuration(200);
    btnOpen->initModules(CHAR2STR("iconOpen"), 33, 33, CHAR2STR("打开文档"), 25, CHAR2STR("打开已知的Cell文档"));
    btnOpen->setFixedSize(250, 81);

    QVBoxLayout *workBtnLayout = new QVBoxLayout;
    workBtnLayout->setSpacing(15);
    workBtnLayout->addWidget(btnNewCode);
    workBtnLayout->addWidget(btnNewGUI);
    workBtnLayout->addWidget(btnOpen);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(btnListWidget);
    leftLayout->addStretch();
    leftLayout->addLayout(workBtnLayout);
    leftLayout->setContentsMargins(40, 30, 0, 200);

    // Set StackedWidget
    settingsPage->getLauncherPtr(this);

    stackedWidget->insertWidget(0, homePage);
    stackedWidget->insertWidget(1, settingsPage);
    stackedWidget->setCurrentIndex(0);

    QHBoxLayout *HLayout = new QHBoxLayout;
    HLayout->addLayout(leftLayout);
    HLayout->addWidget(stackedWidget);
    HLayout->setSpacing(40);

    notificationCenter->setObjectName(CHAR2STR("notificationCenter"));
    notificationCenter->setFixedHeight(25);
    notificationCenter->setBrightDarkColor(Cell::CGL60, Cell::CGL45);

    mainLayout->addWidget(titleBar);
    mainLayout->addLayout(HLayout);
    mainLayout->addWidget(notificationCenter);
    mainLayout->setMargin(0);

    launchGuideDialog();
    settingsPage->showGuideDialog() ? guideDialog->show() : guideDialog->hide();

    if(CellWidgetGlobalInterface::autoSwitch){
        QTime currentTime = QTime::currentTime();
        if((currentTime.hour() >= 19 || currentTime.hour() <= 4) && CellWidgetGlobalInterface::mMode == Cell::ColorScheme::Bright){
            btnListWidget->clickButton(1);
            settingsPage->LauncherSetColorSchemeModeCall(Cell::ColorScheme::Dark);
        }else if(currentTime.hour() < 19 && CellWidgetGlobalInterface::mMode == Cell::ColorScheme::Dark){
            btnListWidget->clickButton(1);
            settingsPage->LauncherSetColorSchemeModeCall(Cell::ColorScheme::Bright);
        }
    }

    CellWidgetGlobalInterface::_modules << titleBar << btnMini << btnMax << btnClose
             << btnListWidget << btnNewCode << btnOpen << notificationCenter
             //<< guideDialog
             << btnNewGUI;
}

void Launcher::setEventConnections(){
    // Setting Page.
    connect(settingsPage, &LauncherSettings::enableColorScheme,  this,         &Launcher::setColorScheme);
    connect(settingsPage, &LauncherSettings::enableColorScheme,  homePage,     &LauncherHomepage::setColorScheme);

    // Guide Dialog.
    connect(guideDialog,  &LauncherGuideDialog::clickedNewPJ,    this,         &Launcher::btnNewClicked);
    connect(guideDialog,  &LauncherGuideDialog::checkBoxClicked, settingsPage, &LauncherSettings::setOnShowGuide);

    // Home Page.
    connect(homePage,     &LauncherHomepage::openFileByPath,     this,         &Launcher::launchClientByPath);

    // BtnListWidget.
    const customListButton *TabHomePage = btnListWidget->getButton(0);
    const customListButton *TabSettings = btnListWidget->getButton(1);
    const customListButton *TabGuide = btnListWidget->getButton(2);
    connect(TabHomePage, &QPushButton::clicked, this, &Launcher::tabHomeClicked);
    connect(TabSettings, &QPushButton::clicked, this, &Launcher::tabSettingsClicked);
    connect(TabGuide,    &QPushButton::clicked, this, &Launcher::launchGuideDialog);

    // Buttons Of Launcher.
    connect(btnNewCode, &QPushButton::clicked, this, &Launcher::btnNewClicked);
    connect(btnNewGUI,  &QPushButton::clicked, this, &Launcher::btnNewGUIClicked);
    connect(btnOpen,    &QPushButton::clicked, this, &Launcher::btnOpenClicked);
    connect(btnMini,    &QPushButton::clicked, this, &Launcher::btnMiniClicked);
    connect(btnMax,     &QPushButton::clicked, this, &Launcher::btnMaxClicked);
    connect(btnClose,   &QPushButton::clicked, [=]{
        close();
    });

#ifndef RELEASE_MODE
    const customListButton *Tab_Test  = btnListWidget->getButton(3);
    connect(Tab_Test, &QPushButton::clicked, [=]{
        testForm->show();
    });
#endif
}

void Launcher::btnMiniClicked(){
    if(this->windowState() != Qt::WindowMinimized)
        this->setWindowState(Qt::WindowMinimized);
}

void Launcher::tabHomeClicked(){
    if(currentPage == PAGE_TYPE::_HOME) return;
    currentPage = PAGE_TYPE::_HOME;
    startPageSwitchAnimation(PAGE_TYPE::_HOME);
}

void Launcher::tabSettingsClicked(){
    if(currentPage == PAGE_TYPE::_SETTINGS) return;
    currentPage = PAGE_TYPE::_SETTINGS;
    startPageSwitchAnimation(PAGE_TYPE::_SETTINGS);
}

void Launcher::startPageSwitchAnimation(PAGE_TYPE nextPage){
    nextPage == PAGE_TYPE::_SETTINGS ?
        CellUiGlobal::setPageSwitchAnimation(stackedWidget, settingsPage, animiPtr):
        CellUiGlobal::setPageSwitchAnimation(stackedWidget, homePage, animiPtr);
}

void Launcher::btnNewClicked(){
    newPJDialog = new LauncherNewPJDialog(CellWidgetGlobalInterface::mMode);
    connect(settingsPage, &LauncherSettings::enableColorScheme, newPJDialog, &LauncherNewPJDialog::setColorScheme);
    connect(newPJDialog,  &LauncherNewPJDialog::projectSettled, [=](CellProjectEntity &entity){
        launchWorkshop();
        workshop->newProject(entity);
    });
    connect(this, &Launcher::launcherClosed, newPJDialog, &LauncherNewPJDialog::close);
    newPJDialog->show();
}

void Launcher::btnNewGUIClicked()
{
    newPJGUI = new LauncherNewPJGUI;
    connect(this, &Launcher::launcherClosed, newPJGUI, &LauncherNewPJGUI::close);
    connect(newPJGUI, &LauncherNewPJGUI::projectSettled, this, &Launcher::launchDeepSense);
    newPJGUI->show();
}

void Launcher::btnOpenClicked()
{
    const QString path = QFileDialog::getOpenFileName(this, "打开Cell文档", ".", "*.workshop");
    if(path == "") return;

    launchClientByPath(CellProjectEntity::judgeDSFromFile(path), path);
}

void Launcher::launchWorkshop(){
    workshop = new Workshop(CellWidgetGlobalInterface::mMode);
    connect(settingsPage, &LauncherSettings::enableColorScheme, workshop, &Workshop::setColorScheme);
    connect(workshop, &Workshop::_constructed,notificationCenter, &notificationCenter::plusCnt);
    connect(workshop, &Workshop::destoryed,notificationCenter, &notificationCenter::minusCnt);
    connect(workshop, &Workshop::projectUpdate, homePage, &LauncherHomepage::insertProject);
    workshop->constructed();
    workshop->show();
}

void Launcher::launchDeepSense()
{
    deepSense = new DeepSense;
    deepSense->show();
}

void Launcher::launchGuideDialog(){
    guideDialog = new LauncherGuideDialog;
    connect(guideDialog,  &LauncherGuideDialog::clickedNewPJ, this, &Launcher::btnNewClicked);
    connect(guideDialog,  &LauncherGuideDialog::checkBoxClicked, settingsPage, &LauncherSettings::setOnShowGuide);
    connect(this, &Launcher::launcherClosed, guideDialog, &LauncherGuideDialog::close);
    MoveToCenter(guideDialog);
    guideDialog->setCheckBox(settingsPage->showGuideDialog());
    guideDialog->show();
}

void Launcher::launchClientByPath(bool isDS, const QString &path)
{
    if(!isDS){
        launchWorkshop();
        workshop->loadFile(path);
    }else{
        launchDeepSense();
    }
}

void Launcher::btnMaxClicked(){
    static QSize size;
    static QPoint point;
    QDesktopWidget *desktopWidget = QApplication::desktop();
    QRect rect = desktopWidget->availableGeometry();
    if(!isMaxSize){
        isMaxSize = true;
        size.setWidth(width());
        size.setHeight(height());
        point = pos();
        resize(rect.width(), rect.height());
        move(0,0);
    }else{
        isMaxSize = false;
        resize(size.width(), size.height());
        move(point);
    }
}

void Launcher::closeEvent(QCloseEvent *e){
    emit launcherClosed();
    e->accept();
}
