#include "Headers/settingspagewidget.h"
#include "ui_settingspagewidget.h"

SettingsPageWidget::SettingsPageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsPageWidget)
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
    // Load style.
    styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowScrollBar.qss"));
    QScrollBar *verticalBar = ui->main_scrollArea->verticalScrollBar();
    verticalBar->setStyleSheet(styleSheetLoader->styleSheet());

    styleSheetLoader->setStyleSheetName(QStringLiteral("SettingsPage_OptionBlock1_BrightBtn.qss"));
    ui->Btn_bright->setStyleSheet(styleSheetLoader->styleSheet());

    styleSheetLoader->setStyleSheetName(QStringLiteral("SettingsPage_OptionBlock1_DarkBtn.qss"));
    ui->Btn_dark->setStyleSheet(styleSheetLoader->styleSheet());

    ui->label_colorScheme->setFont(QFont("微软雅黑", 16));
    ui->label_colorScheme->setStyleSheet("color:#798186");
}

void SettingsPageWidget::on_Btn_bright_clicked()
{
    ui->Btn_dark->setChecked(false);
    ui->radioBtn_bright->setChecked(true);
}

void SettingsPageWidget::on_Btn_dark_clicked()
{
    ui->Btn_bright->setChecked(false);
    ui->radioBtn_dark->setChecked(true);
}
