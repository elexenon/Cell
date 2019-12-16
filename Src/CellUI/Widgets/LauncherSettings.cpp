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
#include <QComboBox>

LauncherSettings::LauncherSettings(QWidget *parent) :
    customFrame(Cell_Const::QSS_CUSTOMFRAME,parent)
    ,label_general(new customLabel(Cell_Const::QSS_CUSTOMLABEL_TRANSPARENT,this))
    ,label_auto_hint(new customLabel(Cell_Const::QSS_CUSTOMLABEL_TRANSPARENT,this))
    ,comboBox_ColorScheme(new QComboBox)
    ,comboBox_Auto(new QComboBox)
    ,LauncherSettings_line_splitter1(new QFrame(this))
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
    setColor(Cell_Const::GRAYLEVEL247);

    using CellEntityTools::styleSheetLoader;

    styleSheetLoader->setStyleSheetName(QStringLiteral("LauncherSettings_OptionBlock1.css"));
    optionBlock1 = new customFrame(styleSheetLoader->styleSheet(), this);
    optionBlock1->setObjectName(QStringLiteral("optionBlock1"));
    optionBlock1->setGeometry(45, 50, 881, 300);
    optionBlock1->setColor(Cell_Const::GRAYLEVEL218);

    styleSheetLoader->setStyleSheetName(QStringLiteral("LauncherSettings_OptionBlock1_ComboBox.css"));
    comboBox_ColorScheme->setStyleSheet(styleSheetLoader->styleSheet());
    comboBox_ColorScheme->setObjectName(QStringLiteral("comboBox_ColorScheme"));
    comboBox_ColorScheme->setParent(optionBlock1);
    comboBox_ColorScheme->setGeometry(200,20,230,30);

    label_colorScheme = new customLabel(Cell_Const::QSS_CUSTOMLABEL_TRANSPARENT,optionBlock1);
    label_colorScheme->setObjectName(QStringLiteral("label_colorScheme"));
    label_colorScheme->setGeometry(145, 22, 120, 25);
    label_colorScheme->setText(tr("外观"));
    label_colorScheme->setFont(QFont(QStringLiteral("微软雅黑 Light"), 11));
    label_colorScheme->setColor(Cell_Const::GRAYLEVEL70);

    styleSheetLoader->setStyleSheetName(QStringLiteral("LauncherSettings_OptionBlock1_ComboBox.css"));
    comboBox_Auto->setStyleSheet(styleSheetLoader->styleSheet());
    comboBox_Auto->setObjectName(QStringLiteral("comboBox_Auto"));
    comboBox_Auto->setParent(optionBlock1);
    comboBox_Auto->setGeometry(200,65,230,30);

    label_auto = new customLabel(Cell_Const::QSS_CUSTOMLABEL_TRANSPARENT,optionBlock1);
    label_auto->setObjectName(QStringLiteral("label_auto"));
    label_auto->setGeometry(108, 67, 120, 25);
    label_auto->setText(tr("自动切换"));
    label_auto->setFont(QFont(QStringLiteral("微软雅黑 Light"), 11));
    label_auto->setColor(Cell_Const::GRAYLEVEL70);

    styleSheetLoader->setStyleSheetName(QStringLiteral("LauncherSettings_OptionBlock2.css"));
    optionBlock2 = new customFrame(styleSheetLoader->styleSheet(), this);
    optionBlock2->setObjectName(QStringLiteral("optionBlock2"));
    optionBlock2->setGeometry(45, 399, 881, 151);
    optionBlock2->setColor(Cell_Const::GRAYLEVEL218);

    label_general->setObjectName(QStringLiteral("label_general"));
    label_general->setGeometry(45, 27, 111, 17);
    label_general->setText(tr("通用"));
    label_general->setFont(QFont(QStringLiteral("微软雅黑 Light")));
    label_general->setColor(Cell_Const::GRAYLEVEL70);

    QFont spacingFont(QStringLiteral("微软雅黑 Light"),8);
    spacingFont.setLetterSpacing(QFont::PercentageSpacing, 102);
    label_auto_hint->setObjectName(QStringLiteral("label_auto_hint"));
    label_auto_hint->setGeometry(45, 203, 400, 17);
    label_auto_hint->setText(tr("将自动在日落后调整为黑暗模式，你也可以选择手动调整。"));
    label_auto_hint->setFont(spacingFont);
    label_auto_hint->setColor(Cell_Const::GRAYLEVEL70);
    label_auto_hint->hide();

    LauncherSettings_line_splitter1 = new QFrame(optionBlock1);
    LauncherSettings_line_splitter1->setObjectName(QString::fromUtf8("LauncherSettings_line_splitter1"));
    LauncherSettings_line_splitter1->setGeometry(QRect(10, 115, 861, 1));
    LauncherSettings_line_splitter1->setStyleSheet("QFrame{color:rgb(180,180,180);}");
    LauncherSettings_line_splitter1->setFrameShadow(QFrame::Plain);
    LauncherSettings_line_splitter1->setFrameShape(QFrame::HLine);

    setEventConnections();
}

void LauncherSettings::setColorScheme(CellGlobal::COLOR_SCHEME mode)
{
    if(mode == m_mode) return;
    m_mode = mode;
    const QColor thisTargetColor = (m_mode == CellGlobal::COLOR_SCHEME::_BRIGHT ?
                                    QColor(247,247,247) : Cell_Const::GRAYLEVEL45);
    const QColor labelGroupTargetColor = (m_mode == CellGlobal::COLOR_SCHEME::_BRIGHT ?
                                    QColor(121,129,134) : Cell_Const::GRAYLEVEL255);
    const QColor blockGroupTargetColor = (m_mode == CellGlobal::COLOR_SCHEME::_BRIGHT ?
                                    Cell_Const::GRAYLEVEL218 : Cell_Const::GRAYLEVEL70);
    CellGlobal::setPropertyAnimation({animi},
                                     "color",
                                     color(),
                                     thisTargetColor,
                                     CellGlobal::CELL_GLOBALANIMIDURATION,
                                     QEasingCurve::InOutCubic,
                                     {this},nullptr);
    CellGlobal::setPropertyAnimation({label_general_animi, label_auto_hint_animi},
                                     "color",
                                     label_general->color(),
                                     labelGroupTargetColor,
                                     CellGlobal::CELL_GLOBALANIMIDURATION,
                                     QEasingCurve::InOutCubic,
                                     {label_general, label_auto_hint},nullptr);
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
    //connect(Btn_bright, SIGNAL(clicked(bool)), this, SLOT(Btn_bright_clicked()));
    //connect(Btn_dark, SIGNAL(clicked(bool)), this, SLOT(Btn_dark_clicked()));
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
