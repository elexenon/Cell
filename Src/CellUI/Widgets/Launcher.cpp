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
//#define RELEASE_MODE

Launcher::Launcher(QWidget *parent)
    : customWinstyleWidget(parent),
      homePage(new LauncherHomepage(this)),
      settingsPage(new LauncherSettings(this)),
      titleBar(new customTitleBar(this)),
      btnMini(new ButtonWithIcon(customButton::Dynamic, titleBar)),
      btnMax(new ButtonWithIcon(customButton::Dynamic, titleBar)),
      btnClose(new ButtonWithIcon(customButton::Dynamic, titleBar)),
      stackedWidget(new QStackedWidget(this)),
      btnNewPJ(new ButtonWithIconTextHint(customButton::DynamicRadius, this)),
      btnOpenPJ(new ButtonWithIconTextHint(customButton::DynamicRadius, this)),
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
Launcher::~Launcher()
{}

const QRect Launcher::maskGeometry()
{
    return QRect(0, titleBar->height(), this->width(),this->height()-titleBar->height()-notificationCenter->height());
}

void Launcher::init()
{
    resize(1400, 800);
    setObjectName(CHAR2STR("Launcher"));
    customWinstyleWidget::LoadWinStyle(this);
    setBrightDarkColor(Cell::CGL247, Cell::CGL30); 
#ifndef RELEASE_MODE
    testForm->hide();
#endif
    // Titlebar Combination.
    titleBar->setFixedHeight(40);
    titleBar->setBrightDarkColor(Cell::CGL255,Cell::CGL45);
    titleBar->setText(CHAR2STR("CELL LAUNCHER"),Cell::CGL130);
    titleBar->setFont(CellUiGlobal::getFont(CHAR2STR("InfoDisplayWeb W01 Medium.ttf"), 21));
    titleBar->setIcon(CHAR2STR("cellLogo28"), 28, 28);
    titleBar->setLeftMargin(15);

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
    btnListWidget->setBrightDarkColor(Cell::CGL247,Cell::CGL30);
    btnListWidget->clickButton(0);

    btnNewPJ->setBrightHoveringColor(Cell::CGL255);
    btnNewPJ->setDarkHoveringColor(Cell::CGL130);
    btnNewPJ->setBrightDarkColor(Cell::CGL218, Cell::CGL70);
    btnNewPJ->setAnimationDuration(150);
    btnNewPJ->initModules(CHAR2STR("btnNewPJ"), 33, 33, CHAR2STR("新建项目"), 25, CHAR2STR("新建一个Cell文档"));
    btnNewPJ->setFixedSize(250, 81);

    btnOpenPJ->setBrightHoveringColor(Cell::CGL255);
    btnOpenPJ->setDarkHoveringColor(Cell::CGL130);
    btnOpenPJ->setBrightDarkColor(Cell::CGL218, Cell::CGL70);
    btnOpenPJ->setAnimationDuration(150);
    btnOpenPJ->initModules(CHAR2STR("btnOpenPJ"), 33, 33, CHAR2STR("打开项目"), 25, CHAR2STR("打开已知的Cell文档"));
    btnOpenPJ->setFixedSize(250, 81);

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
    notificationCenter->setBrightDarkColor(Cell::CGL60, Cell::CGL45);

    QHBoxLayout *HLayoutTitleRight = new QHBoxLayout;
    HLayoutTitleRight->setSpacing(0);
    HLayoutTitleRight->addWidget(btnMini);
    HLayoutTitleRight->addWidget(btnMax);
    HLayoutTitleRight->addWidget(btnClose);
    HLayoutTitleRight->setContentsMargins(0, 0, 0, 0);

    titleBar->addLayout(HLayoutTitleRight);

    guideDialog = new LauncherGuideDialog(this);
    guideDialog->setCheckBox(settingsPage->showGuideDialog());
    settingsPage->showGuideDialog() ? guideDialog->show() : guideDialog->hide();

    _modules << titleBar << btnMini << btnMax << btnClose
             << btnListWidget << btnNewPJ << btnOpenPJ << notificationCenter
             << guideDialog;

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
}

void Launcher::setEventConnections()
{
    // Set connections between SettingsPage & ColorScheme-change-enabled modules
    connect(settingsPage, &LauncherSettings::enableColorScheme, this, &Launcher::setColorScheme);
    connect(settingsPage, &LauncherSettings::enableColorScheme, homePage, &LauncherHomepage::setColorScheme);
    connect(guideDialog,  &LauncherGuideDialog::clickedNewPJ, this, &Launcher::btnNewClicked);
    connect(guideDialog,  &LauncherGuideDialog::checkBoxClicked, settingsPage, &LauncherSettings::setOnShowGuide);
    connect(homePage, &LauncherHomepage::getProjectPath, this, &Launcher::launchWorkShopByPath);
#ifndef RELEASE_MODE
    const customListButton *Tab_Test  = btnListWidget->getButton(3);
    connect(Tab_Test, &QPushButton::clicked, this, &Launcher::tabTestClicked);
#endif
    // Set connections for page-switching buttons.
    const customListButton *Tab_HomePage = btnListWidget->getButton(0);
    const customListButton *Tab_Settings = btnListWidget->getButton(1);
    const customListButton *Tab_Guide = btnListWidget->getButton(2);
    connect(Tab_HomePage, &QPushButton::clicked, this, &Launcher::tabHomeClicked);
    connect(Tab_Settings, &QPushButton::clicked, this, &Launcher::tabSettingsClicked);
    connect(Tab_Guide, &QPushButton::clicked, this, &Launcher::tabGuideClicked);
    connect(btnNewPJ, &QPushButton::clicked, this, &Launcher::btnNewClicked);
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
    int duration = static_cast<int>(Cell::AnimiDuration::GlobalPageSwitchDuration);
    if(nextPage == PAGE_TYPE::_SETTINGS){
        settingsPage->setWindowOpacity(0);
        stackedWidget->setCurrentWidget(settingsPage);
        CellUiGlobal::setFadeInOrOutAnimation(opacityEffect,animiPtr,
                                       settingsPage,duration,Cell::FadeAnimiType::FadeIn);
    }else{
        homePage->setWindowOpacity(0);
        stackedWidget->setCurrentWidget(homePage);
        CellUiGlobal::setFadeInOrOutAnimation(opacityEffect,animiPtr,
                                       homePage,duration,Cell::FadeAnimiType::FadeIn);
    }
}

void Launcher::btnNewClicked()
{

    newPJDialog = nullptr;
    if(newPJDialog == nullptr){
        newPJDialog = new LauncherNewPJDialog(CellWidgetGlobalInterface::mMode, this);
        connect(settingsPage, &LauncherSettings::enableColorScheme, newPJDialog, &LauncherNewPJDialog::setColorScheme);
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
    workshop = new Workshop(CellWidgetGlobalInterface::mMode);
    connect(settingsPage, &LauncherSettings::enableColorScheme, workshop, &Workshop::setColorScheme);
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
