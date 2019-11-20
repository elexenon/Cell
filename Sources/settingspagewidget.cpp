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

#include <QSettings>
#include <QScrollBar>
#include <QPropertyAnimation>
#include <QScrollArea>
#include <QDebug>
#include <QPushButton>
#include <QCheckBox>

using namespace CELL_UTIL;

SettingsPageWidget::SettingsPageWidget(QWidget *parent) :
    customFrame(LITERAL::QSS_CUSTOMFRAME,parent)
    ,optionBlock1(new customFrame(LITERAL::QSS_CUSTOMFRAME_WITH_RADIUS, this))
    ,optionBlock2(new customFrame(LITERAL::QSS_CUSTOMFRAME_WITH_RADIUS, this))
    ,Btn_dark(new QPushButton(this))
    ,Btn_bright(new QPushButton(this))
    ,label_appearence(new customLabel(LITERAL::QSS_CUSTOMLABEL))
    ,label_general(new customLabel(LITERAL::QSS_CUSTOMLABEL))
    ,label_auto_hint(new customLabel(LITERAL::QSS_CUSTOMLABEL,this))
    ,line_color(new QFrame)
    ,m_mode(COLOR_SCHEME::_BRIGHT)
{
    Init();
}

void SettingsPageWidget::mainWindowSetColorSchemeModeCall(COLOR_SCHEME mode)
{
    if(mode == COLOR_SCHEME::_BRIGHT){
        Btn_bright_clicked();
    }else{
        Btn_dark_clicked();
    }
}

void SettingsPageWidget::Init()
{
    setColor(QColor(255,255,255));

    optionBlock1->setObjectName(QStringLiteral("optionBlock1"));
    optionBlock1->setGeometry(45, 20, 881, 151);
    optionBlock1->setColor(QColor(218,218,218));

    optionBlock2->setObjectName(QStringLiteral("optionBlock2"));
    optionBlock2->setGeometry(45, 220, 881, 151);
    optionBlock2->setColor(QColor(218,218,218));

    Btn_bright->setObjectName(QStringLiteral("Btn_bright"));
    Btn_bright->setGeometry(150,20,151,101);
    Btn_bright->setFlat(true);
    Btn_bright->setStyleSheet("border-image: url(:/images/Share/images/ColorScheme_BrightMode_BrightBtn.png);");
    Btn_bright->setCursor(Qt::PointingHandCursor);
    Btn_bright->setParent(optionBlock1);

    Btn_dark->setObjectName(QStringLiteral("Btn_dark"));
    Btn_dark->setGeometry(360,20,151,101);
    Btn_dark->setFlat(true);
    Btn_dark->setStyleSheet("border-image: url(:/images/Share/images/ColorScheme_BrightMode_DarkBtn.png);");
    Btn_dark->setCursor(Qt::PointingHandCursor);
    Btn_dark->setParent(optionBlock1);

    label_appearence->setGeometry(30, 10, 111, 61);
    label_appearence->setText(tr("外观"));
    label_appearence->setFont(QFont(QStringLiteral("Microsoft YaHei UI"), 16));
    label_appearence->setParent(optionBlock1);

    label_general->setGeometry(30, 10, 111, 61);
    label_general->setText(tr("通用"));
    label_general->setFont(QFont(QStringLiteral("Microsoft YaHei UI"), 16));
    label_general->setParent(optionBlock2);

    label_auto_hint->setGeometry(55, 180, 215, 15);
    label_auto_hint->setText(tr("将自动在日落后调整为黑暗模式。"));
    label_auto_hint->setFont(QFont(QStringLiteral("Microsoft YaHei UI")));

    line_color->setParent(this);
    line_color->setGeometry(195, 150, 151, 2);
    line_color->setStyleSheet(QStringLiteral("QFrame{background-color:rgb(121,129,134);}"));
    line_color->setFrameShape(QFrame::VLine);
    line_color->setFrameShadow(QFrame::Plain);

    label_auto_hint->setStyleSheet(QStringLiteral("QLabel{color:#798186;background-color:rgb(255,255,255);}"));

    TOOLS::multiModulesOneStyleSheet({label_appearence,label_general},
                                      QStringLiteral("color:#798186; background-color:#dadada"));

    setEventConnections();
}

void SettingsPageWidget::modulesChangeToDarkness()  // Color_Scheme_Switch.
{   
    if(m_mode == COLOR_SCHEME::_DARK) return;
    m_mode = COLOR_SCHEME::_DARK;

    TOOLS::setPropertyAnimation({label_appearence_animi, label_general_animi, label_auto_hint_animi},
                                 "color",
                                 label_appearence->color(),
                                 QColor(255,255,255),
                                 500,
                                 QEasingCurve::InOutCubic,
                                 {label_appearence, label_general, label_auto_hint},nullptr);
    TOOLS::setPropertyAnimation({line_color_animi},
                                 "pos",
                                 line_color->pos(),
                                 QPoint(405, 150),
                                 500,
                                 QEasingCurve::InOutCubic,
                                 {line_color},nullptr);
    TOOLS::setPropertyAnimation({animi},
                                 "color",
                                 color(),
                                 QColor(44,44,45),
                                 500,
                                 QEasingCurve::InOutCubic,
                                 {this},nullptr);
    TOOLS::setPropertyAnimation({optionBlock1_animi,optionBlock2_animi},
                                 "color",
                                 optionBlock1->color(),
                                 QColor(70,70,70),
                                 500,
                                 QEasingCurve::InOutCubic,
                                 {optionBlock1,optionBlock2},nullptr);
}

void SettingsPageWidget::modulesChangeToBrightness()    // Color_Scheme_Switch.
{
    if(m_mode == COLOR_SCHEME::_BRIGHT) return;
    m_mode = COLOR_SCHEME::_BRIGHT;

    TOOLS::setPropertyAnimation({label_appearence_animi, label_general_animi, label_auto_hint_animi},
                                 "color",
                                 label_appearence->color(),
                                 QColor(121,129,134),
                                 500,
                                 QEasingCurve::InOutCubic,
                                 {label_appearence, label_general, label_auto_hint},nullptr);
    TOOLS::setPropertyAnimation({line_color_animi},
                                 "pos",
                                 line_color->pos(),
                                 QPoint(195, 150),
                                 500,
                                 QEasingCurve::InOutCubic,
                                 {line_color},nullptr);
    TOOLS::setPropertyAnimation({animi},
                                 "color",
                                 color(),
                                 QColor(255,255,255),
                                 500,
                                 QEasingCurve::InOutCubic,
                                 {this},nullptr);
    TOOLS::setPropertyAnimation({optionBlock1_animi,optionBlock2_animi},
                                 "color",
                                 optionBlock1->color(),
                                 QColor(218,218,218),
                                 500,
                                 QEasingCurve::InOutCubic,
                                 {optionBlock1,optionBlock2},nullptr);
}

void SettingsPageWidget::setEventConnections()
{
    connect(Btn_bright, SIGNAL(clicked(bool)), this, SLOT(Btn_bright_clicked()));
    connect(Btn_dark, SIGNAL(clicked(bool)), this, SLOT(Btn_dark_clicked()));
}

void SettingsPageWidget::Btn_bright_clicked()
{
    modulesChangeToBrightness();

    emit enableColorScheme(COLOR_SCHEME::_BRIGHT);
}

void SettingsPageWidget::Btn_dark_clicked()
{
    modulesChangeToDarkness();

    emit enableColorScheme(COLOR_SCHEME::_DARK);
}
