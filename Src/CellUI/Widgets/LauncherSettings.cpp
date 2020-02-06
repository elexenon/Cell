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
#include "../CustomBaseWidgets/customOptionBlock.h"
#include "../CustomBaseWidgets/customOptionBlockItem.h"
#include "../CustomBaseWidgets/customDialogButton.h"
#include "../CustomBaseWidgets/customButton.h"
#include "LauncherSettings.h"

#include <QPropertyAnimation>
#include <QDebug>
#include <QVBoxLayout>

#define DEBUG

LauncherSettings::LauncherSettings(QWidget *parent) :
    customFrame(customFrame::_REGULAR, parent),
    mainLayout(new QVBoxLayout(this)),
    blockGeneral(new customOptionBlock(this, CHAR2STR("通用"))),
    blockGeneral_ItemAppear(new customOptionBlockItem),  
    cBoxAppear(new customDialogButton(CHAR2STR("FUSION"))),
    blockGeneral_ItemAuto(new customOptionBlockItem)
{
    Init();
}

void LauncherSettings::LauncherSetColorSchemeModeCall(CellUiGlobal::COLOR_SCHEME mode)
{
    if(mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT){
        Btn_bright_clicked();
    }else{
        Btn_dark_clicked();
    }
}

void LauncherSettings::Init()
{
    setBrightDarkModeColor(CellUiConst::GRAYLEVEL247,CellUiConst::GRAYLEVEL45);
    setLayout(mainLayout);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(45, 30, 45, 0);
    mainLayout->addWidget(blockGeneral);
    mainLayout->addStretch();

    // ComboBox Appear Combination
    cBoxAppear->setBrightDarkModeColor(CellUiConst::GRAYLEVEL247, CellUiConst::GRAYLEVEL30);
    cBoxAppear->setFixedWidth(200);

    // OptionBlock General Combination.
    blockGeneral->setBrightDarkModeColor(CellUiConst::GRAYLEVEL247, CellUiConst::GRAYLEVEL30);
    // Item Appear Combination.
    blockGeneral_ItemAppear->setTag("外观");
    blockGeneral_ItemAppear->setOptionWidget(cBoxAppear);
    blockGeneral_ItemAppear->setHint("调整Cell的工作主题");
    customDialogButton *cBoxAuto = new customDialogButton(CHAR2STR("是"));
    cBoxAuto->setBrightDarkModeColor(CellUiConst::GRAYLEVEL247, CellUiConst::GRAYLEVEL30);
    cBoxAuto->setFixedWidth(200);
    // Item Auto   Combination.
    blockGeneral_ItemAuto->setTag("自动切换");
    blockGeneral_ItemAuto->setOptionWidget(cBoxAuto);
    blockGeneral_ItemAuto->setHint("在日落时自动切换工作主题");
    blockGeneral->addItem(blockGeneral_ItemAppear, true);
    blockGeneral->addItem(blockGeneral_ItemAuto);
    blockGeneral->tidyItemTags();

    setEventConnections();
}

void LauncherSettings::setColorScheme(CellUiGlobal::COLOR_SCHEME mode)
{
    customFrame::setColorScheme(mode);
}

void LauncherSettings::setEventConnections()
{

}

void LauncherSettings::Btn_bright_clicked()
{
    setColorScheme(CellUiGlobal::COLOR_SCHEME::_BRIGHT);
    emit enableColorScheme(CellUiGlobal::COLOR_SCHEME::_BRIGHT);
}

void LauncherSettings::Btn_dark_clicked()
{
    setColorScheme(CellUiGlobal::COLOR_SCHEME::_DARK);
    emit enableColorScheme(CellUiGlobal::COLOR_SCHEME::_DARK);
}
