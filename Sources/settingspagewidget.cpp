#include "Headers/settingspagewidget.h"
#include "ui_settingspagewidget.h"

SettingsPageWidget::SettingsPageWidget(QWidget *parent) :
    QWidget(parent)
    ,ui(new Ui::SettingsPageWidget)
    ,mainWindowSetColorCall_BRIGHT_Timer(new QTimer(this))
    ,mainWindowSetColorCall_DARK_Timer(new QTimer(this))
    ,main_ScrollArea(new QScrollArea(this))
    ,scrollAreaWidgetContents(new customWidget)
    ,frame_optionBlock2(new customFrame(WINDOW_TYPE::_CHILD))
    ,frame_optionBlock3(new customFrame(WINDOW_TYPE::_CHILD))
    ,frame_optionBlock1(new customFrame(WINDOW_TYPE::_CHILD))
    ,frame_optionBlock4(new customFrame(WINDOW_TYPE::_CHILD))
    ,m_mode(COLOR_SCHEME::_BRIGHT)
{
    ui->setupUi(this);
    Init();
}

SettingsPageWidget::~SettingsPageWidget()
{
    delete ui;
}

void SettingsPageWidget::mainWindowSetColorSchemeModeCall(COLOR_SCHEME mode)
{
    if(mode == COLOR_SCHEME::_BRIGHT){
        switch_bright = true;
        mainWindowSetColorCall_BRIGHT_Timer->start(1000);
    }else{
        switch_dark = true;
        mainWindowSetColorCall_DARK_Timer->start(1000);
    }
}

void SettingsPageWidget::Init()
{
    //Functional.
    connect(mainWindowSetColorCall_BRIGHT_Timer, SIGNAL(timeout()), this, SLOT(on_Btn_bright_clicked()));
    connect(mainWindowSetColorCall_DARK_Timer, SIGNAL(timeout()), this, SLOT(on_Btn_dark_clicked()));

    main_ScrollArea->setGeometry(4, 40, 951, 645);
    main_ScrollArea->setFrameShape(QFrame::NoFrame);
    main_ScrollArea->setFrameShadow(QFrame::Plain);
    main_ScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    main_ScrollArea->setWidgetResizable(true);

    scrollAreaWidgetContents->setGeometry(0, 0, 951, 1000);
    scrollAreaWidgetContents->setMinimumSize(951, 1000);
    main_ScrollArea->setWidget(scrollAreaWidgetContents);

    frame_optionBlock1->setParent(scrollAreaWidgetContents);
    frame_optionBlock1->setGeometry(20, 0, 861, 231);

    frame_optionBlock2->setParent(scrollAreaWidgetContents);
    frame_optionBlock2->setGeometry(20, 260, 861, 151);

    frame_optionBlock3->setParent(scrollAreaWidgetContents);
    frame_optionBlock3->setGeometry(20, 440, 861, 191);

    frame_optionBlock4->setParent(scrollAreaWidgetContents);
    frame_optionBlock4->setGeometry(20, 660, 861, 1000-665);

    ui->label_colorScheme->setParent(frame_optionBlock1);
    ui->label_about->setParent(frame_optionBlock4);
    ui->Btn_bright->setParent(frame_optionBlock1);
    ui->Btn_dark->setParent(frame_optionBlock1);
    ui->radioBtn_bright->setParent(frame_optionBlock1);
    ui->radioBtn_dark->setParent(frame_optionBlock1);
    ui->label_auto->setParent(frame_optionBlock1);
    ui->checkBox_auto->setParent(frame_optionBlock1);
    ui->label_auto_hint->setParent(frame_optionBlock1);

    // Load style.
    styleSheetLoader->setStyleSheetName(QStringLiteral("ScrollBar_Bright.qss"));
    QScrollBar *verticalBar = main_ScrollArea->verticalScrollBar();
    verticalBar->setStyleSheet(styleSheetLoader->styleSheet());

    styleSheetLoader->setStyleSheetName(QStringLiteral("SettingsPage_OptionBlock1_BrightMode_BrightBtn.qss"));
    ui->Btn_bright->setStyleSheet(styleSheetLoader->styleSheet());

    styleSheetLoader->setStyleSheetName(QStringLiteral("SettingsPage_OptionBlock1_BrightMode_DarkBtn.qss"));
    ui->Btn_dark->setStyleSheet(styleSheetLoader->styleSheet());

    ui->label_colorScheme->setFont(QFont(QStringLiteral("微软雅黑"), 16));
    ui->label_colorScheme->setStyleSheet(QStringLiteral("color:#798186; background-color:#dadada"));

    ui->label_about->setFont(QFont(QStringLiteral("微软雅黑"), 16));
    ui->label_about->setStyleSheet(QStringLiteral("color:#798186; background-color:#dadada"));

    styleSheetLoader->setStyleSheetName(QStringLiteral("Frame_OptionBlock_bright.qss"));
    frame_optionBlock1->setStyleSheet(styleSheetLoader->styleSheet());
    frame_optionBlock2->setStyleSheet(styleSheetLoader->styleSheet());
    frame_optionBlock3->setStyleSheet(styleSheetLoader->styleSheet());
    frame_optionBlock4->setStyleSheet(styleSheetLoader->styleSheet());

    ui->radioBtn_bright->setStyleSheet(QStringLiteral("QRadioButton{background-color: #dadada;}"));
    ui->radioBtn_dark->setStyleSheet(QStringLiteral("QRadioButton{background-color: #dadada;}"));

    ui->label_auto->setFont(QFont(QStringLiteral("微软雅黑"), 11));
    ui->label_auto->setStyleSheet(QStringLiteral("color:#798186; background-color:#dadada"));

    ui->label_auto_hint->setStyleSheet(QStringLiteral("color:#798186; background-color:#dadada"));
    ui->label_auto_hint->setFont(QFont(QStringLiteral("微软雅黑 Light")));

    ui->checkBox_auto->setStyleSheet(QStringLiteral("background-color:#dadada"));
}

void SettingsPageWidget::modulesChangeToDarkness()  // Color_Scheme_Switch.
{   
    if(m_mode == COLOR_SCHEME::_DARK) return;
    m_mode = COLOR_SCHEME::_DARK;
    this->setStyleSheet("QWidget{background-color: rgb(31, 30, 31);}");

    UTILITY::setPropertyAnimation(scrollAreaContents_animi, "color", MAINWINDOW_BRIGHT, MAINWINDOW_DARK, 500,
                         QEasingCurve::Linear, scrollAreaWidgetContents, true, nullptr);
    UTILITY::setPropertyAnimation(frame_optionBlock1_animi, "color", frame_optionBlock1->color(), COLOR_OPTION_BLOCK_DARK, 500,
                         QEasingCurve::Linear, frame_optionBlock1, true, nullptr);
    UTILITY::setPropertyAnimation(frame_optionBlock2_animi, "color", frame_optionBlock2->color(), COLOR_OPTION_BLOCK_DARK, 500,
                         QEasingCurve::Linear, frame_optionBlock2, true, nullptr);
    UTILITY::setPropertyAnimation(frame_optionBlock3_animi, "color", frame_optionBlock3->color(), COLOR_OPTION_BLOCK_DARK, 500,
                         QEasingCurve::Linear, frame_optionBlock3, true, nullptr);
    UTILITY::setPropertyAnimation(frame_optionBlock4_animi, "color", frame_optionBlock4->color(), COLOR_OPTION_BLOCK_DARK, 500,
                         QEasingCurve::Linear, frame_optionBlock4, true, nullptr);

    // Ratio Btns.
    ui->radioBtn_bright->setStyleSheet(QStringLiteral("color: #2C2C2D;"));
    ui->radioBtn_dark->setStyleSheet(QStringLiteral("color: #2C2C2D;"));
    // Text Label.
    ui->label_colorScheme->setStyleSheet(QStringLiteral("color:#FFFFFF"));
    ui->label_about->setStyleSheet(QStringLiteral("color:#FFFFFF"));
    // Two Btns.
    styleSheetLoader->setStyleSheetName(QStringLiteral("SettingsPage_OptionBlock1_DarkMode_BrightBtn.qss"));
    ui->Btn_bright->setStyleSheet(styleSheetLoader->styleSheet());
    styleSheetLoader->setStyleSheetName(QStringLiteral("SettingsPage_OptionBlock1_DarkMode_DarkBtn.qss"));
    ui->Btn_dark->setStyleSheet(styleSheetLoader->styleSheet());

    ui->label_auto->setStyleSheet(QStringLiteral("color:#FFFFFF;"));
    ui->label_auto_hint->setStyleSheet(QStringLiteral("color:#FFFFFF;"));
    ui->checkBox_auto->setStyleSheet(QStringLiteral("color:#2c2c2d"));

    // Scroll Bar
    styleSheetLoader->setStyleSheetName(QStringLiteral("ScrollBar_Dark.qss"));
    QScrollBar *verticalBar = main_ScrollArea->verticalScrollBar();
    verticalBar->setStyleSheet(styleSheetLoader->styleSheet());
}

void SettingsPageWidget::modulesChangeToBrightness()    // Color_Scheme_Switch.
{
    if(m_mode == COLOR_SCHEME::_BRIGHT) return;
    m_mode = COLOR_SCHEME::_BRIGHT;
    this->setStyleSheet("QWidget{background-color: rgb(247, 247, 247);}");

    UTILITY::setPropertyAnimation(scrollAreaContents_animi, "color", MAINWINDOW_DARK, MAINWINDOW_BRIGHT, 500,
                         QEasingCurve::Linear, scrollAreaWidgetContents, true, nullptr);
    UTILITY::setPropertyAnimation(frame_optionBlock1_animi, "color", frame_optionBlock1->color(), COLOR_OPTION_BLOCK_BRIGHT, 500,
                         QEasingCurve::Linear, frame_optionBlock1, true, nullptr);
    UTILITY::setPropertyAnimation(frame_optionBlock2_animi, "color", frame_optionBlock2->color(), COLOR_OPTION_BLOCK_BRIGHT, 500,
                         QEasingCurve::Linear, frame_optionBlock2, true, nullptr);
    UTILITY::setPropertyAnimation(frame_optionBlock3_animi, "color", frame_optionBlock3->color(), COLOR_OPTION_BLOCK_BRIGHT, 500,
                         QEasingCurve::Linear, frame_optionBlock3, true, nullptr);
    UTILITY::setPropertyAnimation(frame_optionBlock4_animi, "color", frame_optionBlock4->color(), COLOR_OPTION_BLOCK_BRIGHT, 500,
                         QEasingCurve::Linear, frame_optionBlock4, true, nullptr);
    // Ratio Btns.
    ui->radioBtn_bright->setStyleSheet(QStringLiteral("color: #dadada;"));
    ui->radioBtn_dark->setStyleSheet(QStringLiteral("color: #dadada;"));
    // Text Label.
    ui->label_colorScheme->setStyleSheet(QStringLiteral("color:#798186"));
    ui->label_about->setStyleSheet(QStringLiteral("color:#798186"));
    // Two Btns.
    styleSheetLoader->setStyleSheetName(QStringLiteral("SettingsPage_OptionBlock1_BrightMode_BrightBtn.qss"));
    ui->Btn_bright->setStyleSheet(styleSheetLoader->styleSheet());
    styleSheetLoader->setStyleSheetName(QStringLiteral("SettingsPage_OptionBlock1_BrightMode_DarkBtn.qss"));

    ui->label_auto->setStyleSheet(QStringLiteral("color:#798186;"));
    ui->label_auto_hint->setStyleSheet(QStringLiteral("color:#798186;"));
    ui->checkBox_auto->setStyleSheet(QStringLiteral("color:#dadada"));

    ui->Btn_dark->setStyleSheet(styleSheetLoader->styleSheet());
    // Scroll Bar
    styleSheetLoader->setStyleSheetName(QStringLiteral("ScrollBar_Bright.qss"));
    QScrollBar *verticalBar = main_ScrollArea->verticalScrollBar();
    verticalBar->setStyleSheet(styleSheetLoader->styleSheet());
}

void SettingsPageWidget::on_Btn_bright_clicked()
{

    ui->Btn_dark->setChecked(false);
    ui->radioBtn_bright->setChecked(true);

    modulesChangeToBrightness();

    emit enableColorScheme(COLOR_SCHEME::_BRIGHT);
    if(switch_bright && mainWindowSetColorCall_BRIGHT_Timer)
        delete mainWindowSetColorCall_BRIGHT_Timer;
    switch_bright = false;
}

void SettingsPageWidget::on_Btn_dark_clicked()
{
    ui->Btn_bright->setChecked(false);
    ui->radioBtn_dark->setChecked(true);

    modulesChangeToDarkness();

    emit enableColorScheme(COLOR_SCHEME::_DARK);

    if(switch_dark && mainWindowSetColorCall_DARK_Timer)
        delete mainWindowSetColorCall_DARK_Timer;
    switch_dark = false;
}

void SettingsPageWidget::on_radioBtn_bright_clicked()
{
    ui->Btn_dark->setChecked(false);
    ui->Btn_bright->setChecked(true);
}

void SettingsPageWidget::on_radioBtn_dark_clicked()
{
    ui->Btn_bright->setChecked(false);
    ui->Btn_dark->setChecked(true);
}
