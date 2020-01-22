// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "NewPJProjectCellPage.h"
#include "../../CellCore/Kits/CellUtility.h"
#include "../../CellCore/Kits/StyleSheetLoader.hpp"
#include "../CustomBaseWidgets/customLabel.h"
#include "../CustomBaseWidgets/customFrame.h"

#include <QComboBox>

NewPJProjectCellPage::NewPJProjectCellPage(QWidget *parent):
    customFrame(CellUiConst::QSS_CUSTOMFRAME,parent)
   ,label_title(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT,this))
   ,label_pjConfig(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT,this))
   ,optionBlock1(new customFrame(CellUiConst::QSS_CUSTOMFRAME_RADIUS,this))
   ,label_pjName(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT,optionBlock1))
   ,comboBox1(new QComboBox(optionBlock1))
   ,label_pjLoc(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT,optionBlock1))
   ,comboBox2(new QComboBox(optionBlock1))
   ,label_kitConfig(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT,this))
   ,optionBlock2(new customFrame(CellUiConst::QSS_CUSTOMFRAME_RADIUS,this))
   ,label_version(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT,optionBlock2))
   ,comboBox3(new QComboBox(optionBlock2))
   ,label_encode(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT,optionBlock2))
   ,comboBox4(new QComboBox(optionBlock2))
{
    Init();
}

void NewPJProjectCellPage::Init()
{
    setColor(CellUiConst::GRAYLEVEL247);
    setGeometry(0,0,649,475);

    using CellEntityTools::styleSheetLoader;

    label_title->setObjectName(QStringLiteral("label_title"));
    label_title->setText(tr("连接到Cell运算库。"));
    QFont label_title_font(QStringLiteral("Microsoft YaHei UI Light"));
    label_title_font.setPointSize(14);
    label_title->setFont(label_title_font);
    label_title->setColor(CellUiConst::GRAYLEVEL70);
    label_title->setGeometry(24, 10, 200, 50);

    label_pjConfig->setObjectName(QStringLiteral("label_pjConfig"));
    label_pjConfig->setText(tr("项目属性"));
    QFont label_pjConfig_font(QStringLiteral("Microsoft YaHei UI Light"));
    label_pjConfig_font.setPointSize(8);
    label_pjConfig->setFont(label_pjConfig_font);
    label_pjConfig->setColor(CellUiConst::GRAYLEVEL70);
    label_pjConfig->setGeometry(24,70,100,30);

    styleSheetLoader->setStyleSheetName(QStringLiteral("NewPJDialogCellPage_OptionBlock1.css"));
    optionBlock1->setStyleSheet(styleSheetLoader->styleSheet());
    optionBlock1->setObjectName(QStringLiteral("optionBlock1"));
    optionBlock1->setGeometry(24, 103, 601, 140);
    optionBlock1->setColor(CellUiConst::GRAYLEVEL218);

    label_pjName->setObjectName(QStringLiteral("label_pjName"));
    label_pjName->setText(tr("项目名称"));
    QFont label_pjName_font(QStringLiteral("Microsoft YaHei UI Light"));
    label_pjName_font.setPointSize(11);
    label_pjName->setFont(label_pjName_font);
    label_pjName->setColor(CellUiConst::GRAYLEVEL70);
    label_pjName->setParent(optionBlock1);
    label_pjName->setGeometry(140,25,100,30);

    styleSheetLoader->setStyleSheetName(QStringLiteral("NewPJDialogCellPage_ComboBox1.css"));
    comboBox1->setStyleSheet(styleSheetLoader->styleSheet());
    comboBox1->setObjectName(QStringLiteral("comboBox1"));
    comboBox1->setParent(optionBlock1);
    comboBox1->setGeometry(230,28,160,25);

    label_pjLoc->setObjectName(QStringLiteral("label_pjLoc"));
    label_pjLoc->setText(tr("位置"));
    QFont label_pjLoc_font(QStringLiteral("Microsoft YaHei UI Light"));
    label_pjLoc_font.setPointSize(11);
    label_pjLoc->setFont(label_pjName_font);
    label_pjLoc->setColor(CellUiConst::GRAYLEVEL70);
    label_pjLoc->setParent(optionBlock1);
    label_pjLoc->setGeometry(175,75,100,30);

    styleSheetLoader->setStyleSheetName(QStringLiteral("NewPJDialogCellPage_ComboBox1.css"));
    comboBox2->setStyleSheet(styleSheetLoader->styleSheet());
    comboBox2->setObjectName(QStringLiteral("comboBox2"));
    comboBox2->setParent(optionBlock1);
    comboBox2->setGeometry(230,78,160,25);


}
