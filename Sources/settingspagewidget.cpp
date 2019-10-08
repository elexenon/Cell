#include "Headers/settingspagewidget.h"
#include "ui_settingspagewidget.h"

SettingsPageWidget::SettingsPageWidget(QWidget *parent) :
    QWidget(parent)
    ,ui(new Ui::SettingsPageWidget)
    ,frame_optionBlock2(new customFrame(WINDOW_TYPE::_CHILD))
    ,frame_optionBlock3(new customFrame(WINDOW_TYPE::_CHILD))
    ,frame_optionBlock1(new customFrame(WINDOW_TYPE::_CHILD))
    ,m_mode(COLOR_SCHEME::_BRIGHT)
{
    ui->setupUi(this);
    Init();
}

SettingsPageWidget::~SettingsPageWidget()
{
    delete ui;
}

void SettingsPageWidget::Init()
{
    //Functional.
    frame_optionBlock1->setParent(ui->scrollAreaWidgetContents);
    frame_optionBlock1->setGeometry(20, 0, 861, 231);

    frame_optionBlock2->setParent(ui->scrollAreaWidgetContents);
    frame_optionBlock2->setGeometry(20, 260, 861, 151);

    frame_optionBlock3->setParent(ui->scrollAreaWidgetContents);
    frame_optionBlock3->setGeometry(20, 440, 861, 191);

    ui->label_colorScheme->setParent(frame_optionBlock1);
    ui->Btn_bright->setParent(frame_optionBlock1);
    ui->Btn_dark->setParent(frame_optionBlock1);
    ui->radioBtn_bright->setParent(frame_optionBlock1);
    ui->radioBtn_dark->setParent(frame_optionBlock1);

    // Load style.
    styleSheetLoader->setStyleSheetName(QStringLiteral("ScrollBar_Bright.qss"));
    QScrollBar *verticalBar = ui->main_scrollArea->verticalScrollBar();
    verticalBar->setStyleSheet(styleSheetLoader->styleSheet());

    styleSheetLoader->setStyleSheetName(QStringLiteral("SettingsPage_OptionBlock1_BrightMode_BrightBtn.qss"));
    ui->Btn_bright->setStyleSheet(styleSheetLoader->styleSheet());

    styleSheetLoader->setStyleSheetName(QStringLiteral("SettingsPage_OptionBlock1_BrightMode_DarkBtn.qss"));
    ui->Btn_dark->setStyleSheet(styleSheetLoader->styleSheet());

    ui->label_colorScheme->setFont(QFont(QStringLiteral("微软雅黑"), 16));
    ui->label_colorScheme->setStyleSheet(QStringLiteral("color:#798186; background-color:#dadada"));

    styleSheetLoader->setStyleSheetName(QStringLiteral("Frame_OptionBlock_bright.qss"));
    frame_optionBlock1->setStyleSheet(styleSheetLoader->styleSheet());
    frame_optionBlock2->setStyleSheet(styleSheetLoader->styleSheet());
    frame_optionBlock3->setStyleSheet(styleSheetLoader->styleSheet());

    ui->radioBtn_bright->setStyleSheet(QStringLiteral("QRadioButton{background-color: #dadada;}"));
    ui->radioBtn_dark->setStyleSheet(QStringLiteral("QRadioButton{background-color: #dadada;}"));
}

void SettingsPageWidget::modulesChangeToDarkness()  // Color_Scheme_Switch.
{   
    if(m_mode == COLOR_SCHEME::_DARK) return;
    m_mode = COLOR_SCHEME::_DARK;
    this->setStyleSheet("QWidget{background-color: rgb(31, 30, 31);}");
    ui->scrollAreaWidgetContents->setStyleSheet("QWidget{background-color: rgb(31, 30, 31);}");

    UTILITY::setPropertyAnimation(frame_optionBlock1_animi, "color", frame_optionBlock1->color(), COLOR_OPTION_BLOCK_DARK, 500,
                         QEasingCurve::Linear, frame_optionBlock1, true, nullptr);
    UTILITY::setPropertyAnimation(frame_optionBlock2_animi, "color", frame_optionBlock2->color(), COLOR_OPTION_BLOCK_DARK, 500,
                         QEasingCurve::Linear, frame_optionBlock2, true, nullptr);
    UTILITY::setPropertyAnimation(frame_optionBlock3_animi, "color", frame_optionBlock3->color(), COLOR_OPTION_BLOCK_DARK, 500,
                         QEasingCurve::Linear, frame_optionBlock3, true, nullptr);
    // Ratio Btns.
    ui->radioBtn_bright->setStyleSheet(QStringLiteral("QRadioButton{background-color: #2C2C2D;}"));
    ui->radioBtn_dark->setStyleSheet(QStringLiteral("QRadioButton{background-color: #2C2C2D;}"));
    // Text Label.
    ui->label_colorScheme->setStyleSheet(QStringLiteral("color:#FFFFFF"));
    // Two Btns.
    styleSheetLoader->setStyleSheetName(QStringLiteral("SettingsPage_OptionBlock1_DarkMode_BrightBtn.qss"));
    ui->Btn_bright->setStyleSheet(styleSheetLoader->styleSheet());
    styleSheetLoader->setStyleSheetName(QStringLiteral("SettingsPage_OptionBlock1_DarkMode_DarkBtn.qss"));
    ui->Btn_dark->setStyleSheet(styleSheetLoader->styleSheet());
    // Scroll Area.
    ui->scrollAreaWidgetContents->setStyleSheet("QWidget{background-color:#1F1E1F;}");
    // Scroll Bar
    styleSheetLoader->setStyleSheetName(QStringLiteral("ScrollBar_Dark.qss"));
    QScrollBar *verticalBar = ui->main_scrollArea->verticalScrollBar();
    verticalBar->setStyleSheet(styleSheetLoader->styleSheet());
}

void SettingsPageWidget::modulesChangeToBrightness()    // Color_Scheme_Switch.
{
    if(m_mode == COLOR_SCHEME::_BRIGHT) return;
    m_mode = COLOR_SCHEME::_BRIGHT;
    this->setStyleSheet("QWidget{background-color: rgb(247, 247, 247);}");
    ui->scrollAreaWidgetContents->setStyleSheet("QWidget{background-color: rgb(247, 247, 247);}");

    UTILITY::setPropertyAnimation(frame_optionBlock1_animi, "color", frame_optionBlock1->color(), COLOR_OPTION_BLOCK_BRIGHT, 500,
                         QEasingCurve::Linear, frame_optionBlock1, true, nullptr);
    UTILITY::setPropertyAnimation(frame_optionBlock2_animi, "color", frame_optionBlock2->color(), COLOR_OPTION_BLOCK_BRIGHT, 500,
                         QEasingCurve::Linear, frame_optionBlock2, true, nullptr);
    UTILITY::setPropertyAnimation(frame_optionBlock3_animi, "color", frame_optionBlock3->color(), COLOR_OPTION_BLOCK_BRIGHT, 500,
                         QEasingCurve::Linear, frame_optionBlock3, true, nullptr);
    // Ratio Btns.
    ui->radioBtn_bright->setStyleSheet(QStringLiteral("QRadioButton{background-color: #dadada;}"));
    ui->radioBtn_dark->setStyleSheet(QStringLiteral("QRadioButton{background-color: #dadada;}"));
    // Text Label.
    ui->label_colorScheme->setStyleSheet(QStringLiteral("color:#798186"));
    // Two Btns.
    styleSheetLoader->setStyleSheetName(QStringLiteral("SettingsPage_OptionBlock1_BrightMode_BrightBtn.qss"));
    ui->Btn_bright->setStyleSheet(styleSheetLoader->styleSheet());
    styleSheetLoader->setStyleSheetName(QStringLiteral("SettingsPage_OptionBlock1_BrightMode_DarkBtn.qss"));
    ui->Btn_dark->setStyleSheet(styleSheetLoader->styleSheet());
    // Scroll Area.
    ui->scrollAreaWidgetContents->setStyleSheet("QWidget{background-color:rgb(247, 247, 247);}");
    // Scroll Bar
    styleSheetLoader->setStyleSheetName(QStringLiteral("ScrollBar_Bright.qss"));
    QScrollBar *verticalBar = ui->main_scrollArea->verticalScrollBar();
    verticalBar->setStyleSheet(styleSheetLoader->styleSheet());
}

void SettingsPageWidget::on_Btn_bright_clicked()
{
    ui->Btn_dark->setChecked(false);
    ui->radioBtn_bright->setChecked(true);

    modulesChangeToBrightness();

    emit enableColorScheme(COLOR_SCHEME::_BRIGHT);
}

void SettingsPageWidget::on_Btn_dark_clicked()
{
    ui->Btn_bright->setChecked(false);
    ui->radioBtn_dark->setChecked(true);

    modulesChangeToDarkness();

    emit enableColorScheme(COLOR_SCHEME::_DARK);
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
