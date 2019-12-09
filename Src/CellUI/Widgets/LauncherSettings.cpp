// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "../../CellCore/Kits/StyleSheetLoader.hpp"
#include "../CustomBaseWidgets/customFrame.h"
#include "../CustomBaseWidgets/customLabel.h"
#include "LauncherSettings.h"

#include <QSettings>
#include <QScrollBar>
#include <QPropertyAnimation>
#include <QScrollArea>
#include <QDebug>
#include <QPushButton>
#include <QCheckBox>

LauncherSettings::LauncherSettings(QWidget *parent) :
    customFrame(Cell_Const::QSS_CUSTOMFRAME,parent)
    ,optionBlock1(new customFrame(Cell_Const::QSS_CUSTOMFRAME_WITH_RADIUS, this))
    ,optionBlock2(new customFrame(Cell_Const::QSS_CUSTOMFRAME_WITH_RADIUS, this))
    ,Btn_dark(new QPushButton(this))
    ,Btn_bright(new QPushButton(this))
    ,label_appearence(new customLabel(Cell_Const::QSS_CUSTOMLABEL))
    ,label_general(new customLabel(Cell_Const::QSS_CUSTOMLABEL))
    ,label_auto_hint(new customLabel(Cell_Const::QSS_CUSTOMLABEL,this))
    ,line_color(new QFrame)
    ,m_mode(CellGlobal::COLOR_SCHEME::_BRIGHT)
{
    Init();
}

void LauncherSettings::LauncherSetColorSchemeModeCall(CellGlobal::COLOR_SCHEME mode)
{
    if(mode == CellGlobal::COLOR_SCHEME::_BRIGHT){
        Btn_bright_clicked();
    }else{
        Btn_dark_clicked();
    }
}

void LauncherSettings::Init()
{
    setColor(Cell_Const::GRAYLEVEL255);

    optionBlock1->setObjectName(QStringLiteral("optionBlock1"));
    optionBlock1->setGeometry(45, 0, 881, 151);
    optionBlock1->setColor(Cell_Const::GRAYLEVEL218);

    optionBlock2->setObjectName(QStringLiteral("optionBlock2"));
    optionBlock2->setGeometry(45, 200, 881, 151);
    optionBlock2->setColor(Cell_Const::GRAYLEVEL218);

    Btn_bright->setObjectName(QStringLiteral("Btn_bright"));
    Btn_bright->setGeometry(150,20,151,101);
    Btn_bright->setFlat(true);
    Btn_bright->setStyleSheet("border-image: url(:/images/Images/ColorScheme_BrightMode_BrightBtn.png);");
    Btn_bright->setCursor(Qt::PointingHandCursor);
    Btn_bright->setParent(optionBlock1);

    Btn_dark->setObjectName(QStringLiteral("Btn_dark"));
    Btn_dark->setGeometry(360,20,151,101);
    Btn_dark->setFlat(true);
    Btn_dark->setStyleSheet("border-image: url(:/images/Images/ColorScheme_BrightMode_DarkBtn.png);");
    Btn_dark->setCursor(Qt::PointingHandCursor);
    Btn_dark->setParent(optionBlock1);

    label_appearence->setGeometry(30, 10, 111, 61);
    label_appearence->setText(tr("外观"));
    label_appearence->setFont(QFont(QStringLiteral("微软雅黑 Light"), 16));
    label_appearence->setParent(optionBlock1);

    label_general->setGeometry(30, 10, 111, 61);
    label_general->setText(tr("通用"));
    label_general->setFont(QFont(QStringLiteral("微软雅黑 Light"), 16));
    label_general->setParent(optionBlock2);

    label_auto_hint->setGeometry(55, 160, 215, 15);
    label_auto_hint->setText(tr("将自动在日落后调整为黑暗模式。"));
    label_auto_hint->setFont(QFont(QStringLiteral("Microsoft YaHei UI")));

    line_color->setParent(this);
    line_color->setGeometry(195, 130, 151, 3);
    line_color->setStyleSheet(QStringLiteral("QFrame{background-color:rgb(255,255,255);}"));
    line_color->setFrameShadow(QFrame::Plain);

    label_auto_hint->setStyleSheet(QStringLiteral("QLabel{color:#798186;background-color:rgb(255,255,255);}"));

    CellGlobal::multiModulesOneStyleSheet({label_appearence,label_general},
                                           QStringLiteral("color:#798186; background-color:#dadada"));

    setEventConnections();
}

void LauncherSettings::setColorScheme(CellGlobal::COLOR_SCHEME mode)
{
    if(mode == m_mode) return;
    m_mode = mode;
    const QColor thisTargetColor = (m_mode == CellGlobal::COLOR_SCHEME::_BRIGHT ?
                                    Cell_Const::GRAYLEVEL255 : Cell_Const::GRAYLEVEL45);
    const QColor labelGroupTargetColor = (m_mode == CellGlobal::COLOR_SCHEME::_BRIGHT ?
                                    QColor(121,129,134) : Cell_Const::GRAYLEVEL255);
    const QColor blockGroupTargetColor = (m_mode == CellGlobal::COLOR_SCHEME::_BRIGHT ?
                                    Cell_Const::GRAYLEVEL218 : Cell_Const::GRAYLEVEL70);
    const QPoint lineTargetPos = (m_mode == CellGlobal::COLOR_SCHEME::_BRIGHT ?
                              QPoint(195,130) : QPoint(405,130));
    CellGlobal::setPropertyAnimation({animi},
                                     "color",
                                     color(),
                                     thisTargetColor,
                                     CellGlobal::CELL_GLOBALANIMIDURATION,
                                     QEasingCurve::InOutCubic,
                                     {this},nullptr);
    CellGlobal::setPropertyAnimation({label_appearence_animi, label_general_animi, label_auto_hint_animi},
                                     "color",
                                     label_appearence->color(),
                                     labelGroupTargetColor,
                                     CellGlobal::CELL_GLOBALANIMIDURATION,
                                     QEasingCurve::InOutCubic,
                                     {label_appearence, label_general, label_auto_hint},nullptr);
    CellGlobal::setPropertyAnimation({line_color_animi},
                                     "pos",
                                     line_color->pos(),
                                     lineTargetPos,
                                     CellGlobal::CELL_GLOBALANIMIDURATION,
                                     QEasingCurve::InOutCubic,
                                     {line_color},nullptr);
    CellGlobal::setPropertyAnimation({optionBlock1_animi,optionBlock2_animi},
                                     "color",
                                     optionBlock1->color(),
                                     blockGroupTargetColor,
                                     CellGlobal::CELL_GLOBALANIMIDURATION,
                                     QEasingCurve::InOutCubic,
                                     {optionBlock1,optionBlock2},nullptr);
}

void LauncherSettings::setEventConnections()
{
    connect(Btn_bright, SIGNAL(clicked(bool)), this, SLOT(Btn_bright_clicked()));
    connect(Btn_dark, SIGNAL(clicked(bool)), this, SLOT(Btn_dark_clicked()));
}

void LauncherSettings::Btn_bright_clicked()
{
    setColorScheme(CellGlobal::COLOR_SCHEME::_BRIGHT);
    emit enableColorScheme(CellGlobal::COLOR_SCHEME::_BRIGHT);
}

void LauncherSettings::Btn_dark_clicked()
{
    setColorScheme(CellGlobal::COLOR_SCHEME::_DARK);
    emit enableColorScheme(CellGlobal::COLOR_SCHEME::_DARK);
}
