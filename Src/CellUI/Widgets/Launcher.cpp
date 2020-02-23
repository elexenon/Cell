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
#include "LauncherHomepage.h"
#include "LauncherSettings.h"
#include "WorkShop.h"
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
//#define AUTO_CHANGE
//#define RELEASE_MODE

Launcher::Launcher(QWidget *parent)
    : customWinstyleWidget(parent),
      homePage(new LauncherHomepage(this)),
      settingsPage(new LauncherSettings(this)),
      titleBar(new customTitleBar(this)),
      btnMini(new ButtonWithIcon(customButton::DYNAMIC, titleBar)),
      btnMax(new ButtonWithIcon(customButton::DYNAMIC, titleBar)),
      btnClose(new ButtonWithIcon(customButton::DYNAMIC, titleBar)),
      stackedWidget(new QStackedWidget(this)),
      btnNewPJ(new ButtonWithIconTextHint(customButton::DYNAMIC_RADIUS, this)),
      btnOpenPJ(new ButtonWithIconTextHint(customButton::DYNAMIC_RADIUS, this)),
      notificationCenter(new class notificationCenter(this)),
      btnListWidget(new customButtonListWidget(this)),
#ifndef RELEASE_MODE
      testForm(new CellDevelopTestStation(this)),
#endif
      currentPage(PAGE_TYPE::_HOME)
{
    initLauncher();
    setEventConnections();
}
Launcher::~Launcher()
{}

const QRect Launcher::maskGeometry()
{
    return QRect(0, titleBar->height(), this->width(),this->height()-titleBar->height()-notificationCenter->height());
}

void Launcher::initLauncher()
{
    resize(1400, 800);
    setObjectName(CHAR2STR("Launcher"));
    customWinstyleWidget::LoadWinStyle(this);
    setBrightDarkModeColor(Cell::CGL247, Cell::CGL30); 
#ifndef RELEASE_MODE
    testForm->hide();
#endif
    // Titlebar Combination.
    titleBar->setFixedHeight(40);
    titleBar->setBrightDarkModeColor(Cell::CGL255,Cell::CGL45);
    titleBar->setText(CHAR2STR("CELL LAUNCHER"),Cell::CGL130);
    titleBar->setFont(CellUiGlobal::getFont(CHAR2STR("InfoDisplayWeb W01 Medium.ttf"), 21));
    titleBar->setIcon(CHAR2STR("cellLogo28"), 28, 28);
    titleBar->setLeftMargin(15);

    btnMini->setBrightModeHoveringColor(Cell::NavyBlue);
    btnMini->setDarkModeHoveringColor(Cell::CGL180);
    btnMini->setBrightDarkModeColor(Cell::CGL255, Cell::CGL45);
    btnMini->setAnimationDuration(150);
    btnMini->init(CHAR2STR("iconMinimize"), 15, 2);
    btnMini->setFixedSize(50, titleBar->height());
    btnMini->setCursor(Qt::PointingHandCursor);

    btnMax->setBrightModeHoveringColor(Cell::NavyBlue);
    btnMax->setDarkModeHoveringColor(Cell::CGL180);
    btnMax->setBrightDarkModeColor(Cell::CGL255, Cell::CGL45);
    btnMax->setAnimationDuration(150);
    btnMax->init(CHAR2STR("iconMaximize"), 17, 14);
    btnMax->setFixedSize(50, titleBar->height());
    btnMax->setCursor(Qt::PointingHandCursor);

    btnClose->setBrightModeHoveringColor(Cell::ExitRed);
    btnClose->setDarkModeHoveringColor(Cell::ExitRed);
    btnClose->setBrightDarkModeColor(Cell::CGL255, Cell::CGL45);
    btnClose->setAnimationDuration(150);
    btnClose->init(CHAR2STR("iconClose"), 14, 14);
    btnClose->setFixedSize(50, titleBar->height());
    btnClose->setCursor(Qt::PointingHandCursor);

    // Set SettingsPage
    settingsPage->getLauncherPtr(this);

    // Set StackedWidget
    stackedWidget->insertWidget(0, homePage);
    stackedWidget->insertWidget(1, settingsPage);
    stackedWidget->setCurrentIndex(0);

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
    btnListWidget->setBrightDarkModeColor(Cell::CGL247,Cell::CGL30);
    btnListWidget->clickButton(0);

    btnNewPJ->setBrightModeHoveringColor(Cell::CGL255);
    btnNewPJ->setDarkModeHoveringColor(Cell::CGL255);
    btnNewPJ->setBrightDarkModeColor(Cell::CGL218, Cell::CGL70);
    btnNewPJ->setAnimationDuration(200);
    btnNewPJ->init(CHAR2STR("btnNewPJ"), 33, 33, CHAR2STR("新建项目"), 25, CHAR2STR("新建一个Cell文档"));
    btnNewPJ->setFixedSize(250, 81);
    btnNewPJ->setCursor(Qt::PointingHandCursor);

    btnOpenPJ->setBrightModeHoveringColor(Cell::CGL255);
    btnOpenPJ->setDarkModeHoveringColor(Cell::CGL255);
    btnOpenPJ->setBrightDarkModeColor(Cell::CGL218, Cell::CGL70);
    btnOpenPJ->setAnimationDuration(200);
    btnOpenPJ->init(CHAR2STR("btnOpenPJ"), 33, 33, CHAR2STR("打开项目"), 25, CHAR2STR("打开已知的Cell文档"));
    btnOpenPJ->setFixedSize(250, 81);
    btnOpenPJ->setCursor(Qt::PointingHandCursor);

    QFont t(CHAR2STR("Microsoft Yahei UI Light"));
    t.setPixelSize(25);

    QVBoxLayout *VLayout_WorkBtns = new QVBoxLayout;
    VLayout_WorkBtns->addWidget(btnNewPJ);
    VLayout_WorkBtns->addWidget(btnOpenPJ);
    VLayout_WorkBtns->setSpacing(15);

    QVBoxLayout *VLayout_Left = new QVBoxLayout;
    VLayout_Left->addWidget(btnListWidget);
    VLayout_Left->addStretch();
    VLayout_Left->addLayout(VLayout_WorkBtns);
    VLayout_Left->setContentsMargins(40, 30, 0, 200);

    QHBoxLayout *HLayout = new QHBoxLayout;
    HLayout->addLayout(VLayout_Left);
    HLayout->addWidget(stackedWidget);
    HLayout->setSpacing(40);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(titleBar);
    mainLayout->addLayout(HLayout);
    mainLayout->addWidget(notificationCenter);
    mainLayout->setMargin(0);

    setLayout(mainLayout);

    notificationCenter->setObjectName(CHAR2STR("notificationCenter"));
    notificationCenter->setFixedHeight(25);
    notificationCenter->setBrightDarkModeColor(Cell::CGL70, Cell::CGL45);

    QHBoxLayout *HLayoutTitleRight = new QHBoxLayout;
    HLayoutTitleRight->setSpacing(0);
    HLayoutTitleRight->addWidget(btnMini);
    HLayoutTitleRight->addWidget(btnMax);
    HLayoutTitleRight->addWidget(btnClose);
    HLayoutTitleRight->setContentsMargins(0, 0, 0, 0);

    titleBar->addLayout(HLayoutTitleRight);

    guideDialog = new LauncherGuideDialog(this);
    guideDialog->hide();
#ifdef AUTO_CHANGE
    QTime currentTime = QTime::currentTime();
    if((currentTime.hour() >= 19 || currentTime.hour() <= 4) && m_mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT){
        btnListWidget->clickButton(1);
        settingsPage->LauncherSetColorSchemeModeCall(CellUiGlobal::COLOR_SCHEME::_DARK);
    }else if(currentTime.hour() < 19 && m_mode == CellUiGlobal::COLOR_SCHEME::_DARK){
        btnListWidget->clickButton(1);
        settingsPage->LauncherSetColorSchemeModeCall(CellUiGlobal::COLOR_SCHEME::_BRIGHT);
    }
#endif
}

void Launcher::setEventConnections()
{
    // Set connections between SettingsPage & ColorScheme-change-enabled modules
    connect(settingsPage, &LauncherSettings::enableColorScheme, notificationCenter, &notificationCenter::setColorScheme);
    connect(settingsPage, SIGNAL(enableColorScheme(COLOR_SCHEME)), guideDialog, SLOT(setColorScheme(COLOR_SCHEME)));
    connect(settingsPage, SIGNAL(enableColorScheme(COLOR_SCHEME)), btnNewPJ, SLOT(setColorScheme(COLOR_SCHEME)));
    connect(settingsPage, SIGNAL(enableColorScheme(COLOR_SCHEME)), btnOpenPJ, SLOT(setColorScheme(COLOR_SCHEME)));
    connect(settingsPage, SIGNAL(enableColorScheme(COLOR_SCHEME)), this, SLOT(setColorScheme(COLOR_SCHEME)));
    connect(settingsPage, SIGNAL(enableColorScheme(COLOR_SCHEME)), homePage, SLOT(setColorScheme(COLOR_SCHEME)));
    connect(settingsPage, SIGNAL(enableColorScheme(COLOR_SCHEME)), btnListWidget, SLOT(setColorScheme(COLOR_SCHEME)));
    connect(settingsPage, SIGNAL(enableColorScheme(COLOR_SCHEME)), titleBar, SLOT(setColorScheme(COLOR_SCHEME)));
    connect(guideDialog, &LauncherGuideDialog::clickedNewPJ, this, &Launcher::btnNewClicked);
    connect(homePage, &LauncherHomepage::getProjectPath, this, &Launcher::launchWorkShopByPath);
#ifndef RELEASE_MODE
    const customListButton *Tab_Test  = btnListWidget->getButton(3);
    connect(Tab_Test, SIGNAL(clicked(bool)), this, SLOT(tabTestClicked()));
#endif
    // Set connections for page-switching buttons.
    const customListButton *Tab_HomePage = btnListWidget->getButton(0);
    const customListButton *Tab_Settings = btnListWidget->getButton(1);
    const customListButton *Tab_Guide = btnListWidget->getButton(2);
    connect(Tab_HomePage, SIGNAL(clicked(bool)), this, SLOT(tabHomeClicked()));
    connect(Tab_Settings, SIGNAL(clicked(bool)), this, SLOT(tabSettingsClicked()));
    connect(Tab_Guide, SIGNAL(clicked(bool)), this, SLOT(tabGuideClicked()));
    connect(btnNewPJ, SIGNAL(clicked(bool)), this, SLOT(btnNewClicked()));
    connect(btnOpenPJ, &QPushButton::clicked, this, &Launcher::btnOpenClicked);
    connect(btnMini,  &QPushButton::clicked, this, &Launcher::btnMiniClicked);
    connect(btnMax,   &QPushButton::clicked, this, &Launcher::btnMaxClicked);
    connect(btnClose, &QPushButton::clicked, this, &Launcher::btnCloseClicked);
}

void Launcher::btnMiniClicked()
{
    if(this->windowState() != Qt::WindowMinimized)
            this->setWindowState(Qt::WindowMinimized);
}

void Launcher::btnCloseClicked()
{
    this->close();
    if(workshop){
        workshop->close();
    }
}

void Launcher::tabHomeClicked()
{
    if(currentPage == PAGE_TYPE::_HOME) return;
    currentPage = PAGE_TYPE::_HOME;
    startPageSwitchAnimation(PAGE_TYPE::_HOME);
}

void Launcher::tabSettingsClicked()
{
    if(currentPage == PAGE_TYPE::_SETTINGS) return;
    currentPage = PAGE_TYPE::_SETTINGS;
    startPageSwitchAnimation(PAGE_TYPE::_SETTINGS);
}

void Launcher::tabGuideClicked()
{
    guideDialog->show();
}

void Launcher::tabTestClicked()
{
    testForm->show();
}

void Launcher::startPageSwitchAnimation(PAGE_TYPE nextPage)
{
    int duration = CellUiGlobal::CELL_GLOBALPAGESWITCHDURATION;
    if(nextPage == PAGE_TYPE::_SETTINGS){
        settingsPage->setWindowOpacity(0);
        stackedWidget->setCurrentWidget(settingsPage);
        CellUiGlobal::setFadeInOrOutAnimation(opacityEffect,animi,
                                       settingsPage,duration,CellUiGlobal::FADE_TYPE::_IN);
    }else{
        homePage->setWindowOpacity(0);
        stackedWidget->setCurrentWidget(homePage);
        CellUiGlobal::setFadeInOrOutAnimation(opacityEffect,animi,
                                       homePage,duration,CellUiGlobal::FADE_TYPE::_IN);
    }
}

void Launcher::btnNewClicked()
{
    newPJDialog = nullptr;
    if(newPJDialog == nullptr){
        newPJDialog = new LauncherNewPJDialog(m_mode, this);
        connect(settingsPage, SIGNAL(enableColorScheme(COLOR_SCHEME)),newPJDialog, SLOT(setColorScheme(COLOR_SCHEME)));
        connect(newPJDialog, &LauncherNewPJDialog::projectSettled, this, &Launcher::launchWorkShop);
    }  
    newPJDialog->show();
}

void Launcher::btnOpenClicked()
{
    QString path = QFileDialog::getOpenFileName(this, "打开Cell文档", ".", "*.workshop");
    if(path == "") return;
    launchWorkShopByPath(path);
}

void Launcher::_launcherWorkshop()
{
    workshop = new Workshop(m_mode);
    connect(settingsPage, SIGNAL(enableColorScheme(COLOR_SCHEME)),workshop, SLOT(setColorScheme(COLOR_SCHEME)));
    connect(workshop, &Workshop::_constructed,notificationCenter, &notificationCenter::plusCnt);
    connect(workshop, &Workshop::destoryed,notificationCenter, &notificationCenter::minusCnt);
    connect(workshop, &Workshop::projectUpdate, homePage, &LauncherHomepage::updateDatasByWS);
    workshop->constructed();
    workshop->show();
}

void Launcher::launchWorkShop(CellProjectEntity *entity)
{
    _launcherWorkshop();
    workshop->getProjectEntity(*entity);
}

void Launcher::launchWorkShopByPath(const QString &path)
{
    _launcherWorkshop();
    workshop->loadFile(path);
}

void Launcher::btnMaxClicked()
{
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
