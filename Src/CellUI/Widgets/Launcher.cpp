// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include <QPushButton>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QFontDatabase>
#include <QDebug>
#include <QTime>
#include <QtGlobal>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDesktopWidget>

#include "LauncherGuideDialog.h"
#include "LauncherNewPJDialog.h"
#include "LauncherHomepage.h"
#include "LauncherSettings.h"
#include "WorkShop.h"
#include "Launcher.h"
#include "../CustomBaseWidgets/customWidget.h"
#include "../CustomBaseWidgets/customStaticButton.h"
#include "../CustomBaseWidgets/customDynamicButton.h"
#include "../CustomBaseWidgets/customNotificationCenter.h"
#include "../CustomBaseWidgets/customLabel.h"
#include "../../CellCore/Kits/StyleSheetLoader.hpp"
#include "ui_Launcher.h"
#define CELL_DEBUG
#define ENABLE_WORKSHOP
#define AUTO_CHANGE

Launcher::Launcher(QWidget *parent)
    : customWidget(parent)
    , ui(new Ui::Launcher)
    , workshop(nullptr)
    , homePage(new LauncherHomepage)
    , settingsPage(new LauncherSettings)
    , frame_titleBar(new customFrame(CellUiConst::QSS_CUSTOMFRAME, this))
    , Tab_HomePage(new customStaticButton(this))
    , Tab_Settings(new customStaticButton(this))
    , Tab_Guide(new customStaticButton(this))
    , Btn_NewProject(new customDynamicButton(this))
    , Btn_OpenProject(new customDynamicButton(this))
    , Tab_HomePage_Label(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT,Tab_HomePage))
    , Tab_Settings_Label(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT,Tab_Settings))
    , Tab_Guide_Label(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT,Tab_Guide))
    , Btn_NewProject_Icon(new customLabel(CellUiConst::QSS_CUSTOMLABEL,Btn_NewProject))
    , Btn_NewProject_Function(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT,Btn_NewProject))
    , Btn_NewProject_Hint(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT,Btn_NewProject))
    , Btn_OpenProject_Icon(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT,Btn_OpenProject))
    , Btn_OpenProject_Function(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT,Btn_OpenProject))
    , Btn_OpenProject_Hint(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT,Btn_OpenProject))
    , notificationCenter(new class notificationCenter(CellUiConst::QSS_CUSTOMFRAME, this))
    , tabsGroup(new QButtonGroup(this))
    , currentPage(PAGE_TYPE::_HOME)
    , m_mode(CellUiGlobal::COLOR_SCHEME::_BRIGHT)
{
    ui->setupUi(this);
    InitLauncher();
}
Launcher::~Launcher()
{
    delete ui;
}

void Launcher::setColorScheme(CellUiGlobal::COLOR_SCHEME mode)
{
    if(mode == m_mode) return;
    m_mode = mode;
    const QColor thisTargetColor = (mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT ?
                                    CellUiConst::GRAYLEVEL247 : CellUiConst::GRAYLEVEL30);
    const QColor titleBarTargetColor = (mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT ?
                                    CellUiConst::GRAYLEVEL255 : CellUiConst::GRAYLEVEL45);
    const QColor labelGroupTargetColor = (mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT ?
                                    CellUiConst::GRAYLEVEL70 : CellUiConst::GRAYLEVEL255);
    CellUiGlobal::setPropertyAnimation({this_animi},
                                     "color",
                                     color(),
                                     thisTargetColor,
                                     CellUiGlobal::CELL_GLOBALANIMIDURATION,
                                     QEasingCurve::InOutCubic,
                                     {this}, nullptr);
    CellUiGlobal::setPropertyAnimation({frame_titleBar_animi},
                                     "color",
                                     frame_titleBar->color(),
                                     titleBarTargetColor,
                                     CellUiGlobal::CELL_GLOBALANIMIDURATION,
                                     QEasingCurve::InOutCubic,
                                     {frame_titleBar}, nullptr);
    CellUiGlobal::setPropertyAnimation({Btn_NewProject_Function_animi,Btn_NewProject_Hint_animi,
                                      Btn_OpenProject_Function_animi,Btn_OpenProject_Hint_animi,
                                      Label_HomePage_animi,Label_Settings_animi,Label_Guide_animi},
                                      "color",
                                      Btn_NewProject_Hint->color(),
                                      labelGroupTargetColor,
                                      CellUiGlobal::CELL_GLOBALANIMIDURATION,
                                      QEasingCurve::InOutCubic,
                                      {Btn_NewProject_Function,Btn_NewProject_Hint,
                                       Btn_OpenProject_Function,Btn_OpenProject_Hint,
                                       Tab_HomePage_Label,Tab_Settings_Label,Tab_Guide_Label}, nullptr);
}

void Launcher::InitLauncher()
{
    this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);  // Remove Windows' Default Window Frame.
    customWidget::LoadWinStyle(this);    

    frame_titleBar->setObjectName(QStringLiteral("frame_titleBar"));
    frame_titleBar->setFixedHeight(55);
    frame_titleBar->setColor(CellUiConst::GRAYLEVEL255);

    ui->stackedWidget->insertWidget(1, homePage);
    ui->stackedWidget->insertWidget(2, settingsPage);
    ui->stackedWidget->setCurrentIndex(1);   

    Tab_HomePage->setObjectName(QStringLiteral("Tab_HomePage"));
    Tab_HomePage->setBrightModeCheckedUncheckedColor(CellUiConst::GRAYLEVEL218,CellUiConst::GRAYLEVEL247);
    Tab_HomePage->setDarkModeCheckedUncheckedColor(CellUiConst::GRAYLEVEL70,CellUiConst::GRAYLEVEL30);
    Tab_HomePage->Init();
    Tab_HomePage->setFixedSize(251,31);
    Tab_HomePage->setCheckable(true);
    Tab_HomePage->setChecked(true);

    QFont font(QStringLiteral("Microsoft YaHei UI"));
    font.setPixelSize(16);

    Tab_HomePage_Label->setObjectName(QStringLiteral("Tab_HomePage_Label"));
    Tab_HomePage_Label->setText(QStringLiteral("主页"));
    Tab_HomePage_Label->setFont(font);
    Tab_HomePage_Label->setColor(CellUiConst::GRAYLEVEL70);
    Tab_HomePage_Label->setGeometry(5, 0, 50, 31);

    Tab_Settings->setObjectName(QStringLiteral("Tab_Settings"));
    Tab_Settings->setBrightModeCheckedUncheckedColor(CellUiConst::GRAYLEVEL218,CellUiConst::GRAYLEVEL247);
    Tab_Settings->setDarkModeCheckedUncheckedColor(CellUiConst::GRAYLEVEL70,CellUiConst::GRAYLEVEL30);
    Tab_Settings->Init();
    Tab_Settings->setFixedSize(251,31);
    Tab_Settings->setCheckable(true);

    Tab_Settings_Label->setObjectName(QStringLiteral("Tab_Settings_Label"));
    Tab_Settings_Label->setText(QStringLiteral("选项"));
    Tab_Settings_Label->setFont(font);
    Tab_Settings_Label->setColor(CellUiConst::GRAYLEVEL70);
    Tab_Settings_Label->setGeometry(5, 0, 50, 31);

    Tab_Guide->setObjectName(QStringLiteral("Tab_Guide"));
    Tab_Guide->setBrightModeCheckedUncheckedColor(CellUiConst::GRAYLEVEL218,CellUiConst::GRAYLEVEL247);
    Tab_Guide->setDarkModeCheckedUncheckedColor(CellUiConst::GRAYLEVEL70,CellUiConst::GRAYLEVEL30);
    Tab_Guide->Init();
    Tab_Guide->setFixedSize(251,31);

    Tab_Guide_Label->setObjectName(QStringLiteral("Tab_Guide_Label"));
    Tab_Guide_Label->setText(QStringLiteral("向导"));
    Tab_Guide_Label->setFont(font);
    Tab_Guide_Label->setColor(CellUiConst::GRAYLEVEL70);
    Tab_Guide_Label->setGeometry(5, 0, 50, 31);

    tabsGroup->addButton(Tab_HomePage);
    tabsGroup->addButton(Tab_Settings);
    tabsGroup->setExclusive(true);

    Btn_NewProject->setObjectName(QStringLiteral("Btn_NewProject"));
    Btn_NewProject->setBrightModeEnterLeaveColor(QColor(50,200,230),CellUiConst::GRAYLEVEL218);
    Btn_NewProject->setDarkModeEnterLeaveColor(QColor(50,200,230),CellUiConst::GRAYLEVEL70);
    Btn_NewProject->setAnimationDuration(300);
    Btn_NewProject->Init();
    Btn_NewProject->setFixedSize(251, 81);
    Btn_NewProject->setCursor(Qt::PointingHandCursor);

    Btn_NewProject_Icon->setObjectName(QStringLiteral("Btn_NewProject_Icon"));
    Btn_NewProject_Icon->setStyleSheet("background:transparent;border-image: url(:/images/Images/Btn_NewProject.png);");
    Btn_NewProject_Icon->setGeometry(15,14,35,35);

    QFont t(QStringLiteral("Microsoft Yahei UI Light"));
    t.setPixelSize(25);

    Btn_NewProject_Function->setText(tr("创建新项目(N)"));
    Btn_NewProject_Function->setFont(t);
    Btn_NewProject_Function->setStyleSheet(QStringLiteral("background:transparent;color:rgb(70,70,70);"));
    Btn_NewProject_Function->setGeometry(65, 12, Btn_NewProject_Function->width()+60,Btn_NewProject_Function->height());

    t.setPixelSize(12);
    Btn_NewProject_Hint->setText(tr("创建一个空的Cell文档"));
    Btn_NewProject_Hint->setFont(t);
    Btn_NewProject_Hint->setStyleSheet(QStringLiteral("background:transparent;color:rgb(70,70,70);"));
    Btn_NewProject_Hint->setGeometry(66, 12+Btn_NewProject_Function->height(), Btn_NewProject_Hint->width()+60,Btn_NewProject_Hint->height());

    Btn_OpenProject->setObjectName(QStringLiteral("Btn_OpenProject"));
    Btn_OpenProject->setBrightModeEnterLeaveColor(QColor(50,200,230),CellUiConst::GRAYLEVEL218);
    Btn_OpenProject->setDarkModeEnterLeaveColor(QColor(50,200,230),CellUiConst::GRAYLEVEL70);
    Btn_OpenProject->setAnimationDuration(300);
    Btn_OpenProject->Init();
    Btn_OpenProject->setFixedSize(251, 81);
    Btn_OpenProject->setCursor(Qt::PointingHandCursor);

    Btn_OpenProject_Icon->setObjectName(QStringLiteral("Btn_OpenProject_Icon"));
    Btn_OpenProject_Icon->setStyleSheet("background:transparent;border-image: url(:/images/Images/Btn_OpenProject.png);");
    Btn_OpenProject_Icon->setGeometry(15,14,35,35);
    Btn_OpenProject_Icon->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    t.setPixelSize(25);
    Btn_OpenProject_Function->setText(tr("打开项目(O)"));
    Btn_OpenProject_Function->setFont(t);
    Btn_OpenProject_Function->setStyleSheet(QStringLiteral("background:transparent;color:rgb(70,70,70);"));
    Btn_OpenProject_Function->setGeometry(65, 12, Btn_OpenProject_Function->width()+60,Btn_OpenProject_Function->height());
    Btn_OpenProject_Function->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    t.setPixelSize(12);
    Btn_OpenProject_Hint->setText(tr("打开已有的Cell文档。"));
    Btn_OpenProject_Hint->setFont(t);
    Btn_OpenProject_Hint->setStyleSheet(QStringLiteral("background:transparent;color:rgb(70,70,70);"));
    Btn_OpenProject_Hint->setGeometry(66, 12+Btn_OpenProject_Function->height(), Btn_OpenProject_Function->width()+60,Btn_OpenProject_Function->height());
    Btn_OpenProject_Hint->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    QVBoxLayout *VLayout_Tabs = new QVBoxLayout;
    VLayout_Tabs->addWidget(Tab_HomePage);
    VLayout_Tabs->addWidget(Tab_Settings);
    VLayout_Tabs->addWidget(Tab_Guide);
    VLayout_Tabs->setSpacing(3);

    QVBoxLayout *VLayout_WorkBtns = new QVBoxLayout;
    VLayout_WorkBtns->addWidget(Btn_NewProject);
    VLayout_WorkBtns->addWidget(Btn_OpenProject);
    VLayout_WorkBtns->setSpacing(9);

    QVBoxLayout *VLayout_Left = new QVBoxLayout;
    VLayout_Left->addLayout(VLayout_Tabs);
    VLayout_Left->addStretch();
    VLayout_Left->addLayout(VLayout_WorkBtns);
    VLayout_Left->setContentsMargins(40, 30, 0, 200);

    QHBoxLayout *HLayout = new QHBoxLayout;
    HLayout->addLayout(VLayout_Left);
    HLayout->addWidget(ui->stackedWidget);
    HLayout->setSpacing(40);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(frame_titleBar);
    mainLayout->addLayout(HLayout);
    mainLayout->addWidget(notificationCenter);
    mainLayout->setMargin(0);

    setLayout(mainLayout);

    ui->label_LauncherIcon->setParent(frame_titleBar);
    ui->label_LauncherTitle->setParent(frame_titleBar);
    ui->Btn_max->setParent(frame_titleBar);
    ui->Btn_mini->setParent(frame_titleBar);
    ui->Btn_close->setParent(frame_titleBar);

    notificationCenter->setObjectName(QStringLiteral("notificationCenter"));
    notificationCenter->setFixedHeight(29);
    notificationCenter->setColor(CellUiConst::GRAYLEVEL100);

    int fontID_Info = QFontDatabase::addApplicationFont(CellUiConst::FONT_DIR + QStringLiteral("InfoDisplayWeb W01 Medium.ttf"));
    QString Info = QFontDatabase::applicationFontFamilies(fontID_Info).at(0);

    QFont font_Info(Info);
    font_Info.setPixelSize(23);

    ui->label_LauncherTitle->setFont(font_Info);
    ui->label_LauncherTitle->setStyleSheet(QStringLiteral("color:#798186;"));

    ui->label_LauncherIcon->setFixedSize(25,24);
    ui->Btn_max->setFixedSize(19,19);
    ui->Btn_mini->setFixedSize(19,19);
    ui->Btn_close->setFixedSize(19,19);

    QHBoxLayout *HLayoutTitleLeft = new QHBoxLayout;
    HLayoutTitleLeft->addWidget(ui->label_LauncherIcon);
    HLayoutTitleLeft->addWidget(ui->label_LauncherTitle);
    HLayoutTitleLeft->setSpacing(13);

    QHBoxLayout *HLayoutTitleRight = new QHBoxLayout;
    HLayoutTitleRight->addWidget(ui->Btn_max);
    HLayoutTitleRight->addWidget(ui->Btn_mini);
    HLayoutTitleRight->addWidget(ui->Btn_close);

    QHBoxLayout *HLayoutTitle = new QHBoxLayout;
    HLayoutTitle->addLayout(HLayoutTitleLeft);
    HLayoutTitle->addStretch();
    HLayoutTitle->addLayout(HLayoutTitleRight);
    HLayoutTitle->setContentsMargins(20, 0, 15, 0);

    frame_titleBar->setLayout(HLayoutTitle);

    CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("LauncherCloseBtn.css"));
    ui->Btn_close->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

    CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("LauncherMinimizeBtn.css"));
    ui->Btn_mini->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());

    guideDialog = new LauncherGuideDialog(this);
    guideDialog->show();

    setEventConnections();
#ifdef AUTO_CHANGE
    QTime currentTime = QTime::currentTime();
    if((currentTime.hour() >= 18 || currentTime.hour() <= 4) && m_mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT){
        Tab_Settings_clicked();
        settingsPage->LauncherSetColorSchemeModeCall(CellUiGlobal::COLOR_SCHEME::_DARK);
    }else if(currentTime.hour() < 18 && m_mode == CellUiGlobal::COLOR_SCHEME::_DARK){
        Tab_Settings_clicked();
        settingsPage->LauncherSetColorSchemeModeCall(CellUiGlobal::COLOR_SCHEME::_BRIGHT);
    }
#endif
}

void Launcher::setEventConnections()
{
    // Set connections between SettingsPage & ColorScheme-change-enabled modules.
    connect(settingsPage, SIGNAL(enableColorScheme(COLOR_SCHEME)),
            notificationCenter, SLOT(setColorScheme(COLOR_SCHEME)), Qt::QueuedConnection);
    connect(settingsPage, SIGNAL(enableColorScheme(COLOR_SCHEME)),
            guideDialog, SLOT(setColorScheme(COLOR_SCHEME)), Qt::QueuedConnection);
    connect(settingsPage, SIGNAL(enableColorScheme(COLOR_SCHEME)),
            Tab_HomePage, SLOT(setColorScheme(COLOR_SCHEME)), Qt::QueuedConnection);
    connect(settingsPage, SIGNAL(enableColorScheme(COLOR_SCHEME)),
            Tab_Settings, SLOT(setColorScheme(COLOR_SCHEME)), Qt::QueuedConnection);
    connect(settingsPage, SIGNAL(enableColorScheme(COLOR_SCHEME)),
            Tab_Guide, SLOT(setColorScheme(COLOR_SCHEME)), Qt::QueuedConnection);
    connect(settingsPage, SIGNAL(enableColorScheme(COLOR_SCHEME)),
            Btn_NewProject, SLOT(setColorScheme(COLOR_SCHEME)), Qt::QueuedConnection);
    connect(settingsPage, SIGNAL(enableColorScheme(COLOR_SCHEME)),
            Btn_OpenProject, SLOT(setColorScheme(COLOR_SCHEME)), Qt::QueuedConnection);
    connect(settingsPage, SIGNAL(enableColorScheme(COLOR_SCHEME)),
            this, SLOT(setColorScheme(COLOR_SCHEME)), Qt::QueuedConnection);
    connect(settingsPage, SIGNAL(enableColorScheme(COLOR_SCHEME)),
            homePage, SLOT(setColorScheme(COLOR_SCHEME)), Qt::QueuedConnection);

    // Set connections for page-switching buttons.
    connect(Tab_HomePage, SIGNAL(clicked(bool)), this, SLOT(Tab_HomePage_clicked()));
    connect(Tab_Settings, SIGNAL(clicked(bool)), this, SLOT(Tab_Settings_clicked()));
    connect(Tab_Guide, SIGNAL(clicked(bool)), this, SLOT(Tab_Guide_clicked()));
    connect(Btn_NewProject, SIGNAL(clicked(bool)), this, SLOT(Btn_NewProject_clicked()));
}

void Launcher::on_Btn_mini_clicked()
{
    // 在macOS下有bug
    if(this->windowState() != Qt::WindowMinimized)
            this->setWindowState(Qt::WindowMinimized);
}

void Launcher::on_Btn_close_clicked()
{
    this->close();
    if(workshop){
        workshop->close();
    }
}

void Launcher::Tab_HomePage_clicked()
{
    if(currentPage == PAGE_TYPE::_HOME){
        Tab_HomePage->setChecked(true);
        return;
    }
    currentPage = PAGE_TYPE::_HOME;

    Tab_Settings->setChecked(false);
    Tab_HomePage->setChecked(true);

#ifdef CELL_DEBUG
    qDebug() << "--------------------------";
    qDebug() << "LAUNCHER";
    qDebug() << "HomeBtn_checked:"     << Tab_HomePage->isChecked();
    qDebug() << "SettingsBtn_checked:" << Tab_Settings->isChecked();
    qDebug() << "--------------------------\n";
#endif

    startPageSwitchAnimation(PAGE_TYPE::_HOME);
}

void Launcher::Tab_Settings_clicked()
{
    if(currentPage == PAGE_TYPE::_SETTINGS){
        Tab_Settings->setChecked(true);
        return;
    }

    currentPage = PAGE_TYPE::_SETTINGS;

    Tab_HomePage->setChecked(false);
    Tab_Settings->setChecked(true);

#ifdef CELL_DEBUG
    qDebug() << "--------------------------";
    qDebug() << "LAUNCHER";
    qDebug() << "HomeBtn_checked:"     << Tab_HomePage->isChecked();
    qDebug() << "SettingsBtn_checked:" << Tab_Settings->isChecked();
    qDebug() << "--------------------------\n";
#endif

    startPageSwitchAnimation(PAGE_TYPE::_SETTINGS);
}

void Launcher::Tab_Guide_clicked()
{
    guideDialog->show();
}

void Launcher::startPageSwitchAnimation(PAGE_TYPE nextPage)
{
    int duration = CellUiGlobal::CELL_GLOBALPAGESWITCHDURATION;
    if(nextPage == PAGE_TYPE::_SETTINGS){
        settingsPage->setWindowOpacity(0);
        ui->stackedWidget->setCurrentWidget(settingsPage);
        CellUiGlobal::setFadeInOrOutAnimation(opacityEffect,this_animi,
                                       settingsPage,duration,CellUiGlobal::FADE_TYPE::_IN);
    }else{
        homePage->setWindowOpacity(0);
        ui->stackedWidget->setCurrentWidget(homePage);
        CellUiGlobal::setFadeInOrOutAnimation(opacityEffect,this_animi,
                                       homePage,duration,CellUiGlobal::FADE_TYPE::_IN);
    }
}

bool Launcher::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    return customWidget::nativeEvent(eventType, message, result);
}

void Launcher::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && event->y() <= 60){
        m_move = true;
        m_startPoint = event->globalPos();
        m_windowPoint = this->frameGeometry().topLeft();
    }
}

void Launcher::mouseMoveEvent(QMouseEvent *event)
{
    if (m_move && event->buttons() & Qt::LeftButton){
        QPoint relativePos = event->globalPos() - m_startPoint;
        this->move(m_windowPoint + relativePos );
    }
}

void Launcher::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        m_move = false;
    }
}

void Launcher::Btn_NewProject_clicked()
{
    newPJDialog = new LauncherNewPJDialog(m_mode, this);
    connect(settingsPage, SIGNAL(enableColorScheme(COLOR_SCHEME)),
            newPJDialog, SLOT(setColorScheme(COLOR_SCHEME)), Qt::QueuedConnection);
    newPJDialog->show();
#ifdef ENABLE_WORKSHOP
    workshop = new Workshop(m_mode);
    connect(settingsPage, SIGNAL(enableColorScheme(COLOR_SCHEME)),
            workshop, SLOT(setColorScheme(COLOR_SCHEME)), Qt::QueuedConnection);
    connect(workshop, SIGNAL(constructed()),
            notificationCenter, SLOT(plusCnt()));
    connect(workshop, SIGNAL(destoryed()),
            notificationCenter, SLOT(minusCnt()));
    workshop->_constructed();
    workshop->show();
#endif
}

void Launcher::on_Btn_max_clicked()
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
