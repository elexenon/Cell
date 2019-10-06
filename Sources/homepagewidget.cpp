#include "Headers/homepagewidget.h"
#include "ui_homepagewidget.h"

HomePageWidget::HomePageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomePageWidget)
{
    ui->setupUi(this);
    Init();
}

HomePageWidget::~HomePageWidget()
{
    delete ui;
}

void HomePageWidget::Init()
{

    ui->label_welcome->setFont(QFont("微软雅黑 Light", 18));

    styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowGridBtn.qss"));
    ui->Btn_grid->setStyleSheet(styleSheetLoader->styleSheet());

    styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowListBtn.qss"));
    ui->Btn_list->setStyleSheet(styleSheetLoader->styleSheet());

    ui->label_recentPJ->setFont(QFont("微软雅黑", 12));

    ui->label_sort->setFont(QFont("微软雅黑 Light", 10));
    ui->label_sort->setStyleSheet("color:dadada;");

    styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowScrollBar.qss"));
    QScrollBar *verticalBar = ui->main_scrollArea->verticalScrollBar();
    verticalBar->setStyleSheet(styleSheetLoader->styleSheet());

    styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowComboBox.qss"));
    ui->comboBox_sort->setStyleSheet(styleSheetLoader->styleSheet());
    ui->comboBox_sort->setFont(QFont("微软雅黑"));
}

void HomePageWidget::setAllGraphBtnsUnchecked()
{
    ui->Btn_grid->setChecked(false);
    ui->Btn_list->setChecked(false);
}

void HomePageWidget::on_Btn_grid_clicked()
{
    setAllGraphBtnsUnchecked();
    ui->Btn_grid->setChecked(true);
}

void HomePageWidget::on_Btn_list_clicked()
{
    setAllGraphBtnsUnchecked();
    ui->Btn_list->setChecked(true);
}
