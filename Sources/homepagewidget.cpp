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
    ui->label_welcome->setFont(QFont(QStringLiteral("微软雅黑 Light"), 18));

    styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowGridBtn.qss"));
    ui->Btn_grid->setStyleSheet(styleSheetLoader->styleSheet());

    styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowListBtn.qss"));
    ui->Btn_list->setStyleSheet(styleSheetLoader->styleSheet());

    ui->label_recentPJ->setFont(QFont(QStringLiteral("微软雅黑"), 12));

    ui->label_sort->setFont(QFont(QStringLiteral("微软雅黑 Light"), 10));
    ui->label_sort->setStyleSheet(QStringLiteral("color:dadada;"));

    styleSheetLoader->setStyleSheetName(QStringLiteral("ScrollBar_Bright.qss"));
    QScrollBar *verticalBar = ui->main_scrollArea->verticalScrollBar();
    verticalBar->setStyleSheet(styleSheetLoader->styleSheet());

    styleSheetLoader->setStyleSheetName(QStringLiteral("MainWindowComboBox.qss"));
    ui->comboBox_sort->setStyleSheet(styleSheetLoader->styleSheet());
    ui->comboBox_sort->setFont(QFont(QStringLiteral("微软雅黑")));

    styleSheetLoader->setStyleSheetName(QStringLiteral("Frame_OptionBlock_bright.qss"));
    ui->frame->setStyleSheet(styleSheetLoader->styleSheet());
}

void HomePageWidget::setAllGraphBtnsUnchecked()
{
    ui->Btn_grid->setChecked(false);
    ui->Btn_list->setChecked(false);
}

void HomePageWidget::setColorScheme(COLOR_SCHEME mode)
{
    if(mode == COLOR_SCHEME::_DARK){
        ui->label_welcome->setStyleSheet(QStringLiteral("QLabel{background-color:#1F1E1F; color:#FFFFFF;}"));
        ui->label_sort->setStyleSheet(QStringLiteral("QLabel{background-color:#1F1E1F; color:#FFFFFF;}"));
        ui->label_recentPJ->setStyleSheet(QStringLiteral("QLabel{background-color:#1F1E1F; color:#FFFFFF;}"));
        ui->line->setStyleSheet("QFrame{border:none;background-color:#FFFFFF;"
                                "max-height : 21px;}");

        styleSheetLoader->setStyleSheetName(QStringLiteral("Frame_OptionBlock_dark.qss"));
        ui->frame->setStyleSheet(styleSheetLoader->styleSheet());

        ui->scrollAreaWidgetContents_3->setStyleSheet("QWidget{background-color:#1F1E1F;}");

        styleSheetLoader->setStyleSheetName(QStringLiteral("ScrollBar_Dark.qss"));
        QScrollBar *verticalBar = ui->main_scrollArea->verticalScrollBar();
        verticalBar->setStyleSheet(styleSheetLoader->styleSheet());
    }
    else{
        ui->label_welcome->setStyleSheet(QStringLiteral("QLabel{background-color:#F7F7F7; color:#000000;}"));
        ui->label_sort->setStyleSheet(QStringLiteral("QLabel{background-color:#F7F7F7; color:#000000;}"));
        ui->label_recentPJ->setStyleSheet(QStringLiteral("QLabel{background-color:#F7F7F7; color:#000000;}"));
        ui->line->setStyleSheet("QFrame{border:none;background-color:#DADADA;"
                                               "max-height : 21px;}");
        styleSheetLoader->setStyleSheetName(QStringLiteral("Frame_OptionBlock_bright.qss"));
        ui->frame->setStyleSheet(styleSheetLoader->styleSheet());

        ui->scrollAreaWidgetContents_3->setStyleSheet("QWidget{background-color:rgb(247, 247, 247);}");

        styleSheetLoader->setStyleSheetName(QStringLiteral("ScrollBar_Bright.qss"));
        QScrollBar *verticalBar = ui->main_scrollArea->verticalScrollBar();
        verticalBar->setStyleSheet(styleSheetLoader->styleSheet());
    }
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
