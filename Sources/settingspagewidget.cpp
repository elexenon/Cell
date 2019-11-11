// Copyright 2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "Headers/Kits/qstylesheetloader.hpp"
#include "Headers/Kits/customWidget.h"
#include "Headers/Kits/customFrame.h"
#include "Headers/Kits/customLabel.h"
#include "Headers/settingspagewidget.h"
#include "ui_settingspagewidget.h"

#include <QSettings>
#include <QScrollBar>
#include <QPropertyAnimation>
#include <QScrollArea>
#include <QDebug>

using namespace CELL_UTIL;

SettingsPageWidget::SettingsPageWidget(QWidget *parent) :
    QWidget(parent)
    ,ui(new Ui::SettingsPageWidget)
    ,main_ScrollArea(new QScrollArea(this))
    ,scrollAreaWidgetContents(new customWidget(WIDGET_TYPE::_CHILD))
    ,frame_optionBlock2(new customFrame(FRAME_TYPE::_OPTIONBLOCK))
    ,frame_optionBlock3(new customFrame(FRAME_TYPE::_OPTIONBLOCK))
    ,frame_optionBlock1(new customFrame(FRAME_TYPE::_OPTIONBLOCK))
    ,frame_optionBlock4(new customFrame(FRAME_TYPE::_OPTIONBLOCK))
    ,label_appearence(new customLabel)
    ,label_automation(new customLabel)
    ,label_auto_hint(new customLabel)
    ,label_license(new customLabel)
    ,label_lice_hint(new customLabel)
    ,label_about(new customLabel)
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
    qDebug() << "yes";
    if(mode == COLOR_SCHEME::_BRIGHT){
        on_Btn_bright_clicked();
    }else{
        on_Btn_dark_clicked();
    }
}

void SettingsPageWidget::Init()
{
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

    label_appearence->setParent(frame_optionBlock1);
    label_appearence->setGeometry(30, 10, 111, 61);
    label_appearence->setText(tr("外观"));
    label_appearence->setFont(QFont(QStringLiteral("微软雅黑"), 16));

    label_automation->setParent(frame_optionBlock1);
    label_automation->setGeometry(33, 189, 61, 31);
    label_automation->setText(tr("自动化"));
    label_automation->setFont(QFont(QStringLiteral("微软雅黑"), 11));

    label_auto_hint->setParent(frame_optionBlock1);
    label_auto_hint->setGeometry(122, 179, 501, 51);
    label_auto_hint->setText(tr("勾选此项时,Cell会自动根据系统时间设定相应的颜色模式。"));
    label_auto_hint->setFont(QFont(QStringLiteral("微软雅黑 Light")));

    label_license->setParent(frame_optionBlock2);
    label_license->setGeometry(30, 10, 111, 61);
    label_license->setText(tr("许可"));
    label_license->setFont(QFont(QStringLiteral("微软雅黑"), 16));

    label_lice_hint->setParent(frame_optionBlock2);
    label_lice_hint->setGeometry(150, 20, 731, 81);
    label_lice_hint->setText(tr("此自由软件使用GUN GPLv3开源协议。若您想由此软件衍生新的程序，请务必开放源码\n\n请勿对由此软件衍生的产品进行任何闭源商业行为。"));
    label_lice_hint->setFont(QFont(QStringLiteral("微软雅黑"),10));

    label_about->setParent(frame_optionBlock3);
    label_about->setGeometry(30, 10, 111, 61);
    label_about->setText(tr("关于"));
    label_about->setFont(QFont(QStringLiteral("微软雅黑"), 16));

    using TOOLS::styleSheetLoader;

    ui->Btn_bright->setParent(frame_optionBlock1);
    styleSheetLoader->setStyleSheetName(QStringLiteral("SettingsPage_OptionBlock1_BrightMode_BrightBtn.css"));
    ui->Btn_bright->setStyleSheet(styleSheetLoader->styleSheet());

    ui->Btn_dark->setParent(frame_optionBlock1);
    styleSheetLoader->setStyleSheetName(QStringLiteral("SettingsPage_OptionBlock1_BrightMode_DarkBtn.css"));
    ui->Btn_dark->setStyleSheet(styleSheetLoader->styleSheet());

    ui->checkBox_auto->setParent(frame_optionBlock1);
    ui->checkBox_auto->setStyleSheet(QStringLiteral("background-color:#dadada"));

    ui->labelGPL->setParent(frame_optionBlock2);
    ui->labelGPL->setGeometry(730,99,ui->labelGPL->width(),ui->labelGPL->height());

    styleSheetLoader->setStyleSheetName(QStringLiteral("ScrollBar_Bright.css"));
    QScrollBar *verticalBar = main_ScrollArea->verticalScrollBar();
    verticalBar->setStyleSheet(styleSheetLoader->styleSheet());

    TOOLS::multiModulesOneStyleSheet({label_appearence,label_automation,label_auto_hint,
                                      label_license,label_lice_hint,label_about},
                                      QStringLiteral("color:#798186; background-color:#dadada"));

    ui->radioBtn_bright->setParent(frame_optionBlock1);
    ui->radioBtn_dark->setParent(frame_optionBlock1);
    TOOLS::multiModulesOneStyleSheet({ui->radioBtn_bright,ui->radioBtn_dark},
                                      QStringLiteral("QRadioButton{background-color: #dadada;}"));

    styleSheetLoader->setStyleSheetName(QStringLiteral("Frame_OptionBlock_bright.css"));
    frame_optionBlock1->setStyleSheet(styleSheetLoader->styleSheet());
    frame_optionBlock2->setStyleSheet(styleSheetLoader->styleSheet());
    frame_optionBlock3->setStyleSheet(styleSheetLoader->styleSheet());
    frame_optionBlock4->setStyleSheet(styleSheetLoader->styleSheet());
}

void SettingsPageWidget::modulesChangeToDarkness()  // Color_Scheme_Switch.
{   
    if(m_mode == COLOR_SCHEME::_DARK) return;
    m_mode = COLOR_SCHEME::_DARK;
    this->setStyleSheet("QWidget{background-color: rgb(31, 30, 31);}");

    TOOLS::setPropertyAnimation({scrollAreaContents_animi},
                                 "color",
                                 scrollAreaWidgetContents->color(),
                                 LITERAL::MAINWINDOW_DARK,
                                 500,
                                 QEasingCurve::InOutCubic,
                                 {scrollAreaWidgetContents},nullptr);

    TOOLS::setPropertyAnimation({frame_optionBlock1_animi,frame_optionBlock2_animi,
                                 frame_optionBlock3_animi,frame_optionBlock4_animi},
                                 "color",
                                 frame_optionBlock1->color(),
                                 LITERAL::COLOR_OPTION_BLOCK_DARK,
                                 500,
                                 QEasingCurve::InOutCubic,
                                 {frame_optionBlock1,frame_optionBlock2,
                                  frame_optionBlock3,frame_optionBlock4},nullptr);

    TOOLS::setPropertyAnimation({label_appearence_animi, label_automation_animi, label_auto_hint_animi,
                                 label_license_animi, label_lice_hint_animi, label_about_animi},
                                 "color",
                                 label_about->color(),
                                 QColor(255,255,255),
                                 500,
                                 QEasingCurve::InOutCubic,
                                 {label_appearence, label_automation, label_auto_hint,
                                  label_license, label_lice_hint, label_about},nullptr);
    // Ratio Btns.
    TOOLS::multiModulesOneStyleSheet({ui->radioBtn_bright,ui->radioBtn_dark},
                                      QStringLiteral("color: #2C2C2D;"));

    // Two Btns.
    using TOOLS::styleSheetLoader;
    styleSheetLoader->setStyleSheetName(QStringLiteral("SettingsPage_OptionBlock1_DarkMode_BrightBtn.css"));
    ui->Btn_bright->setStyleSheet(styleSheetLoader->styleSheet());

    styleSheetLoader->setStyleSheetName(QStringLiteral("SettingsPage_OptionBlock1_DarkMode_DarkBtn.css"));
    ui->Btn_dark->setStyleSheet(styleSheetLoader->styleSheet());

    ui->checkBox_auto->setStyleSheet(QStringLiteral("color:#2c2c2d"));

    // Scroll Bar
    styleSheetLoader->setStyleSheetName(QStringLiteral("ScrollBar_Dark.css"));
    QScrollBar *verticalBar = main_ScrollArea->verticalScrollBar();
    verticalBar->setStyleSheet(styleSheetLoader->styleSheet());
}

void SettingsPageWidget::modulesChangeToBrightness()    // Color_Scheme_Switch.
{
    if(m_mode == COLOR_SCHEME::_BRIGHT) return;
    m_mode = COLOR_SCHEME::_BRIGHT;
    this->setStyleSheet("QWidget{background-color: rgb(247, 247, 247);}");


    TOOLS::setPropertyAnimation({scrollAreaContents_animi},
                                 "color",
                                 scrollAreaWidgetContents->color(),
                                 LITERAL::MAINWINDOW_BRIGHT,
                                 500,
                                 QEasingCurve::InOutCubic,
                                 {scrollAreaWidgetContents},nullptr);

    TOOLS::setPropertyAnimation({frame_optionBlock1_animi,frame_optionBlock2_animi,
                                 frame_optionBlock3_animi,frame_optionBlock4_animi},
                                 "color",
                                 frame_optionBlock1->color(),
                                 LITERAL::COLOR_OPTION_BLOCK_BRIGHT,
                                 500,
                                 QEasingCurve::InOutCubic,
                                 {frame_optionBlock1,frame_optionBlock2,
                                  frame_optionBlock3,frame_optionBlock4},nullptr);

    TOOLS::setPropertyAnimation({label_appearence_animi, label_automation_animi, label_auto_hint_animi,
                                 label_license_animi, label_lice_hint_animi, label_about_animi},
                                 "color",
                                 label_about->color(),
                                 QColor(121,129,134),
                                 500,
                                 QEasingCurve::InOutCubic,
                                 {label_appearence, label_automation, label_auto_hint,
                                  label_license, label_lice_hint, label_about},nullptr);

    // Ratio Btns.
    TOOLS::multiModulesOneStyleSheet({ui->radioBtn_bright,ui->radioBtn_dark},
                                      QStringLiteral("color: #dadada;"));
    // Two Btns.
    using TOOLS::styleSheetLoader;
    styleSheetLoader->setStyleSheetName(QStringLiteral("SettingsPage_OptionBlock1_BrightMode_BrightBtn.css"));
    ui->Btn_bright->setStyleSheet(styleSheetLoader->styleSheet());
    styleSheetLoader->setStyleSheetName(QStringLiteral("SettingsPage_OptionBlock1_BrightMode_DarkBtn.css"));

    ui->checkBox_auto->setStyleSheet(QStringLiteral("color:#dadada"));

    ui->Btn_dark->setStyleSheet(styleSheetLoader->styleSheet());
    // Scroll Bar
    styleSheetLoader->setStyleSheetName(QStringLiteral("ScrollBar_Bright.css"));
    QScrollBar *verticalBar = main_ScrollArea->verticalScrollBar();
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
