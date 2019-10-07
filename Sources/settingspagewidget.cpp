#include "Headers/settingspagewidget.h"
#include "ui_settingspagewidget.h"

SettingsPageWidget::SettingsPageWidget(QWidget *parent) :
    QWidget(parent)
    ,ui(new Ui::SettingsPageWidget)
    ,optionBlocks(new QList<QFrame*>)

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
    optionBlocks->append(ui->frame_optionBlock1);
    optionBlocks->append(ui->frame_optionBlock2);
    optionBlocks->append(ui->frame_optionBlock3);

    // Load style.
    styleSheetLoader->setStyleSheetName(QStringLiteral("ScrollBar_Bright.qss"));
    QScrollBar *verticalBar = ui->main_scrollArea->verticalScrollBar();
    verticalBar->setStyleSheet(styleSheetLoader->styleSheet());

    styleSheetLoader->setStyleSheetName(QStringLiteral("SettingsPage_OptionBlock1_BrightMode_BrightBtn.qss"));
    ui->Btn_bright->setStyleSheet(styleSheetLoader->styleSheet());

    styleSheetLoader->setStyleSheetName(QStringLiteral("SettingsPage_OptionBlock1_BrightMode_DarkBtn.qss"));
    ui->Btn_dark->setStyleSheet(styleSheetLoader->styleSheet());

    ui->label_colorScheme->setFont(QFont(QStringLiteral("微软雅黑"), 16));
    ui->label_colorScheme->setStyleSheet(QStringLiteral("color:#798186"));

    styleSheetLoader->setStyleSheetName(QStringLiteral("Frame_OptionBlock_bright.qss"));
    ui->frame_optionBlock1->setStyleSheet(styleSheetLoader->styleSheet());
    ui->frame_optionBlock2->setStyleSheet(styleSheetLoader->styleSheet());
    ui->frame_optionBlock3->setStyleSheet(styleSheetLoader->styleSheet());

    ui->radioBtn_bright->setStyleSheet(QStringLiteral("QRadioButton{background-color: #dadada;}"));
    ui->radioBtn_dark->setStyleSheet(QStringLiteral("QRadioButton{background-color: #dadada;}"));
}

void SettingsPageWidget::modulesChangeToDarkness()
{
    this->setStyleSheet("background-color: rgb(31, 30, 31);");
    // Option Blocks.
    styleSheetLoader->setStyleSheetName(QStringLiteral("Frame_OptionBlock_dark.qss"));
    for(auto & e : *optionBlocks)
        e->setStyleSheet(styleSheetLoader->styleSheet());
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

void SettingsPageWidget::modulesChangeToBrightness()
{
    this->setStyleSheet("background-color: rgb(247, 247, 247);");
    // Option Blocks.
    styleSheetLoader->setStyleSheetName(QStringLiteral("Frame_OptionBlock_bright.qss"));
    for(auto & e : *optionBlocks)
        e->setStyleSheet(styleSheetLoader->styleSheet());
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
