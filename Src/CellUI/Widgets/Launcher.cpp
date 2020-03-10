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
      btnNewCode(new ButtonWithIconTextHint(customButton::DynamicRadius, this)),
      btnNewGUI(new ButtonWithIconTextHint(customButton::DynamicRadius, this)),
      btnOpen(new ButtonWithIconTextHint(customButton::DynamicRadius, this)),
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

const QRect Launcher::maskGeometry(){
    return QRect(0, titleBar->height(), this->width(),this->height()-titleBar->height()-notificationCenter->height());
}

void Launcher::init(){
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

    QFont t(CHAR2STR("Microsoft Yahei UI Light"));
    t.setPixelSize(25);

    QVBoxLayout *VLayout_WorkBtns = new QVBoxLayout;
    VLayout_WorkBtns->addWidget(btnNewCode);
    VLayout_WorkBtns->addWidget(btnNewGUI);
    VLayout_WorkBtns->addWidget(btnOpen);
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

    _launchGuideDialog();
    settingsPage->showGuideDialog() ? guideDialog->show() : guideDialog->hide();

    _modules << titleBar << btnMini << btnMax << btnClose
             << btnListWidget << btnNewCode << btnOpen << notificationCenter
             //<< guideDialog
             << btnNewGUI;

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

void Launcher::setEventConnections(){
    // Set connections between SettingsPage & ColorScheme-change-enabled modules
    connect(settingsPage, &LauncherSettings::enableColorScheme,  this,         &Launcher::setColorScheme);
    connect(settingsPage, &LauncherSettings::enableColorScheme,  homePage,     &LauncherHomepage::setColorScheme);
    connect(guideDialog,  &LauncherGuideDialog::clickedNewPJ,    this,         &Launcher::btnNewClicked);
    connect(guideDialog,  &LauncherGuideDialog::checkBoxClicked, settingsPage, &LauncherSettings::setOnShowGuide);
    connect(homePage,     &LauncherHomepage::getProjectPath,     this,         &Launcher::launchWorkShopByPath);
    // Set connections for page-switching buttons.
    const customListButton *Tab_HomePage = btnListWidget->getButton(0);
    const customListButton *Tab_Settings = btnListWidget->getButton(1);
    const customListButton *Tab_Guide = btnListWidget->getButton(2);
    connect(Tab_HomePage, &QPushButton::clicked, this, &Launcher::tabHomeClicked);
    connect(Tab_Settings, &QPushButton::clicked, this, &Launcher::tabSettingsClicked);
    connect(Tab_Guide, &QPushButton::clicked, [=]{
        _launchGuideDialog();
    });
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

void Launcher::btnNewClicked(){
    newPJDialog = new LauncherNewPJDialog(CellWidgetGlobalInterface::mMode);
    connect(settingsPage, &LauncherSettings::enableColorScheme, newPJDialog, &LauncherNewPJDialog::setColorScheme);
    connect(newPJDialog, &LauncherNewPJDialog::projectSettled, this, &Launcher::launchWorkShop);
    connect(this, &Launcher::launcherClosed, newPJDialog, &LauncherNewPJDialog::close);
    newPJDialog->show();
}

void Launcher::btnNewGUIClicked()
{
    newPJGUI = new LauncherNewPJGUI;
    connect(this, &Launcher::launcherClosed, newPJGUI, &LauncherNewPJGUI::close);
    newPJGUI->show();
}

void Launcher::btnOpenClicked(){

    QString path = QFileDialog::getOpenFileName(this, "打开Cell文档", ".", "*.workshop");
    if(path == "") return;
    launchWorkShopByPath(path);
}

void Launcher::_launchWorkshop(){
    workshop = new Workshop(CellWidgetGlobalInterface::mMode);
    connect(settingsPage, &LauncherSettings::enableColorScheme, workshop, &Workshop::setColorScheme);
    connect(workshop, &Workshop::_constructed,notificationCenter, &notificationCenter::plusCnt);
    connect(workshop, &Workshop::destoryed,notificationCenter, &notificationCenter::minusCnt);
    connect(workshop, &Workshop::projectUpdate, homePage, &LauncherHomepage::updateDatasByWS);
    workshop->constructed();
    workshop->show();
}

void Launcher::_launchGuideDialog(){
    guideDialog = new LauncherGuideDialog;
    MoveToCenter(guideDialog);
    connect(guideDialog,  &LauncherGuideDialog::clickedNewPJ, this, &Launcher::btnNewClicked);
    connect(guideDialog,  &LauncherGuideDialog::checkBoxClicked, settingsPage, &LauncherSettings::setOnShowGuide);
    connect(this, &Launcher::launcherClosed, guideDialog, &LauncherGuideDialog::close);
    guideDialog->setCheckBox(settingsPage->showGuideDialog());
    guideDialog->show();
}

void Launcher::launchWorkShop(CellProjectEntity *entity){
    _launchWorkshop();
    workshop->getProjectEntity(*entity);
}

void Launcher::launchWorkShopByPath(const QString &path){
    _launchWorkshop();
    workshop->loadFile(path);
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
