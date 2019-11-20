// Copyright 2019 CellTek.
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

#include "Headers/guidedialog.h"
#include "Headers/homepagewidget.h"
#include "Headers/settingspagewidget.h"
#include "Headers/workshop.h"
#include "Headers/mainwindow.h"
#include "Headers/Kits/customFrame.h"
#include "Headers/Kits/customStaticButton.h"
#include "Headers/Kits/customDynamicButton.h"
#include "Headers/Kits/customLabel.h"
#include "Headers/Kits/qstylesheetloader.hpp"
#include "ui_mainwindow.h"

using namespace CELL_UTIL;

mainWindow::mainWindow(QWidget *parent)
    : customWidget(WIDGET_TYPE::_BASE, parent)
    , ui(new Ui::mainWindow)
    , workshop(nullptr)
    , homePage(new HomePageWidget)
    , settingsPage(new SettingsPageWidget)
    , frame_titleBar(new customFrame(LITERAL::QSS_CUSTOMFRAME, this))
    , Tab_HomePage(new customStaticButton(this))
    , Tab_Settings(new customStaticButton(this))
    , Tab_Guide(new customStaticButton(this))
    , Btn_NewProject(new customDynamicButton(this))
    , Btn_OpenProject(new customDynamicButton(this))
    , Btn_NewProject_Icon(new QLabel(this))
    , Btn_NewProject_Function(new QLabel(this))
    , Btn_NewProject_Hint(new QLabel(this))
    , currentPage(PAGE_TYPE::_HOME)
    , m_mode(COLOR_SCHEME::_BRIGHT)
{
    ui->setupUi(this);
    InitMainWindow();
}
mainWindow::~mainWindow()
{
    delete ui;
}

void mainWindow::setColorScheme(COLOR_SCHEME mode)
{
    using TOOLS::styleSheetLoader;
    if(mode == COLOR_SCHEME::_BRIGHT){
        if(mode == m_mode) return;
        m_mode = COLOR_SCHEME::_BRIGHT;
        TOOLS::setPropertyAnimation({propertyAnimi},
                                     "color",
                                     color(),
                                     LITERAL::MAINWINDOW_BRIGHT,
                                     500,
                                     QEasingCurve::InOutCubic,
                                     {this}, nullptr);
        TOOLS::setPropertyAnimation({propertyAnimi},
                                     "color",
                                     frame_titleBar->color(),
                                     QColor(255,255,255),
                                     500,
                                     QEasingCurve::InOutCubic,
                                     {frame_titleBar}, nullptr);

        TOOLS::multiModulesOneStyleSheet({ui->Label_HomePage,ui->Label_Settings,ui->Label_Guide},
                                         QStringLiteral("QLabel{color:rgb(0,0,0);background:transparent;}"));

        TOOLS::multiModulesOneStyleSheet({Btn_NewProject_Function,Btn_NewProject_Hint},
                                         QStringLiteral("background:transparent;color:rgb(70,70,70);"));

        styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowMaxBtn_bright.css"));
        ui->Btn_max->setStyleSheet(styleSheetLoader->styleSheet());
        styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowMinimizeBtn_bright.css"));
        ui->Btn_mini->setStyleSheet(styleSheetLoader->styleSheet());
        styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowCloseBtn_bright.css"));
        ui->Btn_close->setStyleSheet(styleSheetLoader->styleSheet());
    }
    else{
        if(mode == m_mode) return;
        m_mode = COLOR_SCHEME::_DARK;
        TOOLS::setPropertyAnimation({propertyAnimi},
                                     "color",
                                     color(),
                                     LITERAL::MAINWINDOW_DARK,
                                     500,
                                     QEasingCurve::InOutCubic,
                                     {this}, nullptr);
        TOOLS::setPropertyAnimation({propertyAnimi},
                                     "color",
                                     frame_titleBar->color(),
                                     QColor(44,44,45),
                                     500,
                                     QEasingCurve::InOutCubic,
                                     {frame_titleBar}, nullptr);

        TOOLS::multiModulesOneStyleSheet({ui->Label_HomePage,ui->Label_Settings,ui->Label_Guide},
                                         QStringLiteral("QLabel{color:rgb(255,255,255);background:transparent;}"));

        TOOLS::multiModulesOneStyleSheet({Btn_NewProject_Function,Btn_NewProject_Hint},
                                         QStringLiteral("background:transparent;color:rgb(255,255,255);"));

        styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowMaxBtn_dark.css"));
        ui->Btn_max->setStyleSheet(styleSheetLoader->styleSheet());
        styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowMinimizeBtn_dark.css"));
        ui->Btn_mini->setStyleSheet(styleSheetLoader->styleSheet());
        styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowCloseBtn_dark.css"));
        ui->Btn_close->setStyleSheet(styleSheetLoader->styleSheet());
    }
}

void mainWindow::InitMainWindow()
{
    this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);  // Remove Windows' Default Window Frame.
    customWidget::LoadWinStyle(this);    

    frame_titleBar->setGeometry(0, 0, 1311, 61);
    frame_titleBar->setColor(QColor(255, 255, 255));

    settingsPage->setAutoFillBackground(true);

    ui->stackedWidget->insertWidget(1, homePage);
    ui->stackedWidget->insertWidget(2, settingsPage);
    ui->stackedWidget->setCurrentIndex(1);

    Tab_HomePage->setObjectName(QStringLiteral("Tab_HomePage"));
    Tab_HomePage->setBrightModeCheckedUncheckedColor(QColor(218,218,218),QColor(247,247,247));
    Tab_HomePage->setDarkModeCheckedUncheckedColor(QColor(70,70,70),QColor(30,31,30));
    Tab_HomePage->Init();
    Tab_HomePage->setGeometry(40, 101, 251, 31);
    Tab_HomePage->setCheckable(true);
    Tab_HomePage->setChecked(true);

    Tab_Settings->setObjectName(QStringLiteral("Tab_Settings"));
    Tab_Settings->setBrightModeCheckedUncheckedColor(QColor(218,218,218),QColor(247,247,247));
    Tab_Settings->setDarkModeCheckedUncheckedColor(QColor(70,70,70),QColor(30,31,30));
    Tab_Settings->Init();
    Tab_Settings->setGeometry(40, 135, 251, 31);
    Tab_Settings->setCheckable(true);

    Tab_Guide->setObjectName(QStringLiteral("Tab_Guide"));
    Tab_Guide->setBrightModeCheckedUncheckedColor(QColor(218,218,218),QColor(247,247,247));
    Tab_Guide->setDarkModeCheckedUncheckedColor(QColor(70,70,70),QColor(30,31,30));
    Tab_Guide->Init();
    Tab_Guide->setGeometry(40, 169, 251, 31);

    ui->Label_HomePage->setFont(QFont(QStringLiteral("Microsoft YaHei UI"),10));
    ui->Label_HomePage->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    ui->Label_Settings->setFont(QFont(QStringLiteral("Microsoft YaHei UI"),10));
    ui->Label_Settings->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    ui->Label_Guide->setFont(QFont(QStringLiteral("Microsoft YaHei UI"),10));
    ui->Label_Guide->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    Btn_NewProject->setObjectName(QStringLiteral("Btn_NewProject"));
    Btn_NewProject->setBrightModeEnterLeaveColor(QColor(15,187,255),QColor(218,218,218));
    Btn_NewProject->setDarkModeEnterLeaveColor(QColor(15,187,255),QColor(70,70,70));
    Btn_NewProject->setAnimationDuration(500);
    Btn_NewProject->Init();
    Btn_NewProject->setGeometry(40, 331, 251, 81);

    Btn_NewProject_Icon->setObjectName(QStringLiteral("Btn_NewProject_Icon"));
    Btn_NewProject_Icon->setStyleSheet("background:transparent;border-image: url(:/images/Share/images/Btn_NewProject.png);");
    Btn_NewProject_Icon->setGeometry(55,345,35,35);
    Btn_NewProject_Icon->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    Btn_NewProject_Function->setText(tr("创建新项目(N)"));
    Btn_NewProject_Function->setFont(QFont(QStringLiteral("Microsoft YaHei UI"), 15));
    Btn_NewProject_Function->setStyleSheet(QStringLiteral("background:transparent;color:rgb(70,70,70);"));
    Btn_NewProject_Function->setGeometry(105, 345, Btn_NewProject_Function->width()+60,Btn_NewProject_Function->height());
    Btn_NewProject_Function->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    Btn_NewProject_Hint->setText(tr("创建一个空的Cell文档"));
    Btn_NewProject_Hint->setFont(QFont(QStringLiteral("Microsoft YaHei UI"), 7));
    Btn_NewProject_Hint->setStyleSheet(QStringLiteral("background:transparent;color:rgb(70,70,70);"));
    Btn_NewProject_Hint->setGeometry(106, 343+Btn_NewProject_Function->height(), Btn_NewProject_Hint->width()+60,Btn_NewProject_Hint->height());
    Btn_NewProject_Hint->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    Btn_OpenProject->setObjectName(QStringLiteral("Btn_OpenProject"));
    Btn_OpenProject->setBrightModeEnterLeaveColor(QColor(15,187,255),QColor(218,218,218));
    Btn_OpenProject->setDarkModeEnterLeaveColor(QColor(15,187,255),QColor(70,70,70));
    Btn_OpenProject->setAnimationDuration(500);
    Btn_OpenProject->Init();
    Btn_OpenProject->setGeometry(40, 421, 251, 81);

    ui->label_mainWindowIcon->setParent(frame_titleBar);
    ui->label_mainWindowTitle->setParent(frame_titleBar);
    ui->Btn_max->setParent(frame_titleBar);
    ui->Btn_mini->setParent(frame_titleBar);
    ui->Btn_close->setParent(frame_titleBar);

    int fontID_Info = QFontDatabase::addApplicationFont(LITERAL::FONT_DIR + QStringLiteral("InfoDisplayWeb W01 Medium.ttf"));
    QString Info = QFontDatabase::applicationFontFamilies(fontID_Info).at(0);

    using TOOLS::styleSheetLoader;

    QFont font_Info(Info, 14);
    font_Info.setLetterSpacing(QFont::PercentageSpacing, 100);

    ui->label_mainWindowTitle->setFont(font_Info);
    ui->label_mainWindowTitle->setStyleSheet("color:"+LITERAL::COLOR_SPACE_GRAY+";");

    styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowCloseBtn_bright.css"));
    ui->Btn_close->setStyleSheet(styleSheetLoader->styleSheet());

    styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowMinimizeBtn_bright.css"));
    ui->Btn_mini->setStyleSheet(styleSheetLoader->styleSheet());

    guideDialog = new GuideDialog(this);
    guideDialog->show();

    connect(settingsPage, SIGNAL(enableColorScheme(COLOR_SCHEME)),
            guideDialog, SLOT(setColorScheme(COLOR_SCHEME)), Qt::QueuedConnection);

    setEventConnections();

    QTime currentTime = QTime::currentTime();
    if((currentTime.hour() >= 18 || currentTime.hour() <= 4) && m_mode == COLOR_SCHEME::_BRIGHT){
        Tab_Settings_clicked();
        settingsPage->mainWindowSetColorSchemeModeCall(COLOR_SCHEME::_DARK);
    }else if(currentTime.hour() < 18 && m_mode == COLOR_SCHEME::_DARK){
        Tab_Settings_clicked();
        settingsPage->mainWindowSetColorSchemeModeCall(COLOR_SCHEME::_BRIGHT);
    }
}

void mainWindow::setEventConnections()
{
    // Set connections between SettingsPage & ColorScheme-change-enabled modules.
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

void mainWindow::on_Btn_mini_clicked()
{
    // 在macOS下有bug
    if(this->windowState() != Qt::WindowMinimized)
            this->setWindowState(Qt::WindowMinimized);
}

void mainWindow::on_Btn_close_clicked()
{
    this->close();
    if(workshop){
        workshop->close();
    }
}

void mainWindow::Tab_HomePage_clicked()
{
    if(currentPage == PAGE_TYPE::_HOME){
        Tab_HomePage->setChecked(true);
        return;
    }
    currentPage = PAGE_TYPE::_HOME;

    Tab_Settings->setChecked(false);
    Tab_HomePage->setChecked(true);

#ifdef CELL_DEBUG
    qDebug()<<"HomeBtn_checked:"<<Tab_HomePage->isChecked();
    qDebug()<<"SettingsBtn_checked:"<<Tab_Settings->isChecked();
#endif

    startPageSwitchAnimation(PAGE_TYPE::_HOME);
}

void mainWindow::Tab_Settings_clicked()
{
    if(currentPage == PAGE_TYPE::_SETTINGS){
        Tab_Settings->setChecked(true);
        return;
    }

    currentPage = PAGE_TYPE::_SETTINGS;

    Tab_HomePage->setChecked(false);
    Tab_Settings->setChecked(true);

#ifdef CELL_DEBUG
    qDebug()<<"HomeBtn_checked:"<<Tab_HomePage->isChecked();
    qDebug()<<"SettingsBtn_checked:"<<Tab_Settings->isChecked();
#endif

    startPageSwitchAnimation(PAGE_TYPE::_SETTINGS);
}

void mainWindow::Tab_Guide_clicked()
{
    guideDialog->show();
}
// This function is to set fade animation for
//
// the specified module using "setPropertyAnimation".
void mainWindow::startFadeInOrOutAnimation(QWidget *target, int duration, FADE_TYPE type)
{
    int startValue = 0, endValue = 1;
    if(type == FADE_TYPE::_OUT)
        qSwap(startValue, endValue);
    opacityEffect = new QGraphicsOpacityEffect(target);
    opacityEffect->setOpacity(startValue);
    target->setGraphicsEffect(opacityEffect);
    TOOLS::setPropertyAnimation({propertyAnimi}, "opacity", startValue, endValue, duration,
                         QEasingCurve::Linear, {nullptr}, opacityEffect);
}

void mainWindow::startPageSwitchAnimation(PAGE_TYPE nextPage)
{
    int duration = 200;
    if(nextPage == PAGE_TYPE::_SETTINGS){
        settingsPage->setWindowOpacity(0);
        ui->stackedWidget->setCurrentWidget(settingsPage);
        startFadeInOrOutAnimation(settingsPage, duration, FADE_TYPE::_IN);
    }else{
        homePage->setWindowOpacity(0);
        ui->stackedWidget->setCurrentWidget(homePage);
        startFadeInOrOutAnimation(homePage, duration, FADE_TYPE::_IN);
    }
}

#ifdef Q_OS_WIN32
bool mainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    return customWidget::nativeEvent(eventType, message, result);
}
#endif
// Mouse drag process.
void mainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && event->y() <= 60){
        m_move = true;
        m_startPoint = event->globalPos();
        m_windowPoint = this->frameGeometry().topLeft();
    }
}

void mainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_move && event->buttons() & Qt::LeftButton){
        QPoint relativePos = event->globalPos() - m_startPoint;
        this->move(m_windowPoint + relativePos );
    }
}

void mainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        m_move = false;
    }
}

void mainWindow::Btn_NewProject_clicked()
{
    workshop = new Workshop(m_mode);
    connect(settingsPage, SIGNAL(enableColorScheme(COLOR_SCHEME)),
            workshop, SLOT(setColorScheme(COLOR_SCHEME)), Qt::QueuedConnection);
    workshop->show();
    this->on_Btn_mini_clicked();
}
