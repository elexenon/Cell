#include "Headers/mainwindow.h"
#include "ui_mainwindow.h"
#define DEBUG

mainWindow::mainWindow(QWidget *parent)
    : DropShadowWidget(parent)
    , ui(new Ui::mainWindow)
    , mainWindowTabBtns(new QList<QPushButton*>)
    , homePage(new HomePageWidget)
    , settingsPage(new SettingsPageWidget)
    , currentPage(PAGE_TYPE::_HOME)
{
    ui->setupUi(this);
    InitMainWindow();
}
mainWindow::~mainWindow()
{
    delete ui;
}

#ifdef Q_OS_WIN32
bool mainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    return DropShadowWidget::nativeEvent(eventType, message, result);
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

void mainWindow::setColorScheme(COLOR_SCHEME mode)
{
    QPixmap tmp;
    if(mode == COLOR_SCHEME::_BRIGHT){
        tmp.load(IMG_DIR+QStringLiteral("labelCell.png"));

        this->setStyleSheet("background-color: rgb(247, 247, 247);");

        ui->frame_titleBar->setStyleSheet(QStringLiteral("QFrame{background-color:#FFFFFF}"));
    }
    else{
        tmp.load(IMG_DIR+QStringLiteral("labelCell_dark.png"));

        this->setStyleSheet(QStringLiteral("background-color: rgb(31, 30, 31);"));

        ui->frame_titleBar->setStyleSheet(QStringLiteral("QFrame{background-color:#2C2C2D}"));
    }
    ui->label_backGND->setPixmap(tmp);
}

void mainWindow::InitMainWindow()
{
    // Functional.
    this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);  // Remove Windows' Default Window Frame.
#ifdef ROUNDED_WINDOW
    this->setAttribute(Qt::WA_TranslucentBackground);
#endif

#ifdef Q_OS_WIN32
    DropShadowWidget::LoadWinStyle(this);
#endif

    connect(settingsPage, SIGNAL(enableColorScheme(COLOR_SCHEME)),
            this, SLOT(setColorScheme(COLOR_SCHEME)), Qt::QueuedConnection);

    connect(settingsPage, SIGNAL(enableColorScheme(COLOR_SCHEME)),
            homePage, SLOT(setColorScheme(COLOR_SCHEME)), Qt::QueuedConnection);

    mainWindowTabBtns->append(ui->Btn_HomePage);
    mainWindowTabBtns->append(ui->Btn_Settings);

    ui->stackedWidget->addWidget(homePage);
    ui->stackedWidget->addWidget(settingsPage);
    ui->stackedWidget->setCurrentWidget(homePage);

    // Load Custom Fonts.
    int fontID_Info = QFontDatabase::addApplicationFont(FONT_DIR + QStringLiteral("InfoDisplayWeb W01 Medium.ttf"));
    QString Info = QFontDatabase::applicationFontFamilies(fontID_Info).at(0);
#ifdef DEBUG
    qDebug() << QStringLiteral("Main Window Title Font: ") << Info;
#endif

    // Load Styles.
    QFont font_Info(Info, 14);
    font_Info.setLetterSpacing(QFont::PercentageSpacing, 100);
    ui->label_mainWindowTitle->setFont(font_Info);
    ui->label_mainWindowTitle->setStyleSheet("color:"+COLOR_SPACE_GRAY+";");

    ui->label_welcome->setFont(QFont(QStringLiteral("微软雅黑 Light"), 18));

    styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowLeftTab_HomePage.qss"));
    ui->Btn_HomePage->setStyleSheet(styleSheetLoader->styleSheet());

    styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowLeftTab_Settings.qss"));
    ui->Btn_Settings->setStyleSheet(styleSheetLoader->styleSheet());

    styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowLeftTab_Guide.qss"));
    ui->Btn_Guide->setStyleSheet(styleSheetLoader->styleSheet());

    styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowLeftTab_NewPJ.qss"));
    ui->Btn_NewProject->setStyleSheet(styleSheetLoader->styleSheet());

    styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowLeftTab_OpenPJ.qss"));
    ui->Btn_OpenProject->setStyleSheet(styleSheetLoader->styleSheet());

    styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowCloseBtn.qss"));
    ui->Btn_close->setStyleSheet(styleSheetLoader->styleSheet());

    styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowMinimizeBtn.qss"));
    ui->Btn_mini->setStyleSheet(styleSheetLoader->styleSheet());

    // Functional;
    guideDialog = new GuideDialog(this);
    //guideDialog->show();
}

void mainWindow::setAllTabsUnchecked()
{
    for(auto & e : *mainWindowTabBtns)
        e->setChecked(false);
}

void mainWindow::startPageSwitchAnimation(PAGE_TYPE nextPage)
{
    int duration = 200;
    if(nextPage == PAGE_TYPE::_SETTINGS){
        settingsPage->setWindowOpacity(0);
        ui->stackedWidget->setCurrentWidget(settingsPage);
        startFadeInOrOutAnimation(settingsPage, ui->stackedWidget, duration, FADE_TYPE::_IN);
    }else{
        homePage->setWindowOpacity(0);
        ui->stackedWidget->setCurrentWidget(homePage);
        startFadeInOrOutAnimation(homePage, ui->stackedWidget, duration, FADE_TYPE::_IN);
    }
}

void mainWindow::on_Btn_mini_clicked()
{
    if(this->windowState() != Qt::WindowMinimized)
            this->setWindowState(Qt::WindowMinimized);    // 在macOS下有bug
}

void mainWindow::on_Btn_close_clicked()
{
    close();
}

void mainWindow::on_Btn_HomePage_clicked()
{
    if(currentPage == PAGE_TYPE::_HOME)
        return;
    currentPage = PAGE_TYPE::_HOME;
    setAllTabsUnchecked();
    ui->Btn_HomePage->setChecked(true);
    startPageSwitchAnimation(PAGE_TYPE::_HOME);
}

void mainWindow::on_Btn_Settings_clicked()
{
    if(currentPage == PAGE_TYPE::_SETTINGS)
        return;
    currentPage = PAGE_TYPE::_SETTINGS;
    setAllTabsUnchecked();
    ui->Btn_Settings->setChecked(true);
    startPageSwitchAnimation(PAGE_TYPE::_SETTINGS);
}

void mainWindow::on_Btn_Guide_clicked()
{
    guideDialog->show();
}

void mainWindow::startFadeInOrOutAnimation(QWidget *target, QWidget *parent, int duration, FADE_TYPE type)
{
    int startValue = 0, endValue = 1;
    if(type == FADE_TYPE::_OUT)
        qSwap(startValue, endValue);
    opacityEffect = new QGraphicsOpacityEffect(target);
    opacityEffect->setOpacity(startValue);
    target->setGraphicsEffect(opacityEffect);
    setPropertyAnimation("opacity", startValue, endValue, duration, QEasingCurve::Linear, nullptr, opacityEffect, parent);
}

void mainWindow::setPropertyAnimation(QByteArray _property, QVariant startValue, QVariant endValue, int duration,
                                      QEasingCurve curve, QWidget *target = nullptr, QGraphicsEffect* effect = nullptr, QWidget* _parent = nullptr)
{
    if(!effect)
        propertyAnimi = new QPropertyAnimation(target, _property);
    else
        propertyAnimi = new QPropertyAnimation(effect, _property, _parent);
    propertyAnimi->setDuration(duration);
    propertyAnimi->setEasingCurve(curve);
    propertyAnimi->setStartValue(startValue);
    propertyAnimi->setEndValue(endValue);
    propertyAnimi->start(QAbstractAnimation::DeleteWhenStopped);
}
