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
#include "../CustomBaseWidgets/customOptionBlock.h"
#include "../CustomBaseWidgets/customOptionBlockItem.h"
#include "../CustomBaseWidgets/customComboBox.h"

#include <QComboBox>
#include <QVBoxLayout>

NewPJProjectCellPage::NewPJProjectCellPage(QWidget *parent):
    customFrame(CellUiConst::QSS_CUSTOMFRAME,parent)
   ,mainLayout(new QVBoxLayout)
   ,label_title(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT,this))
   ,blockConfig(new customOptionBlock(this, CHAR2STR("项目属性")))
   ,blockConfig_Name(new customOptionBlockItem)
   ,cBoxName(new customComboBox(CHAR2STR("Project")))
   ,blockConfig_Loca(new customOptionBlockItem)
   ,cBoxLoca(new customComboBox(CHAR2STR("Location")))
{
    Init();
}

void NewPJProjectCellPage::Init()
{
    setBrightDarkModeColor(CellUiConst::GRAYLEVEL247, CellUiConst::GRAYLEVEL30);
    setLayout(mainLayout);

    mainLayout->setContentsMargins(50, 20, 50, 0);
    mainLayout->addWidget(label_title);
    mainLayout->addStretch(1);
    mainLayout->addWidget(blockConfig);
    mainLayout->addStretch(6);

    using CellEntityTools::styleSheetLoader;

    CellUiGlobal::setCustomTextLabel(label_title, CHAR2STR("Microsoft YaHei UI Light"), 24, CHAR2STR("连接到Cell运算库。"));

    cBoxName->setBrightDarkModeColor(CellUiConst::GRAYLEVEL255, CellUiConst::GRAYLEVEL45);
    cBoxName->setFixedWidth(200);
    cBoxLoca->setBrightDarkModeColor(CellUiConst::GRAYLEVEL255, CellUiConst::GRAYLEVEL45);
    cBoxLoca->setFixedWidth(200);

    // OptionBlock Configuration Combination.
    blockConfig->setBrightDarkModeColor(CellUiConst::GRAYLEVEL247, CellUiConst::GRAYLEVEL30);
        // Item Name Combination.
        blockConfig_Name->setTag(CHAR2STR("名称"));
        blockConfig_Name->setOptionWidget(cBoxName);
        blockConfig_Name->setHint("设置项目名称");
        // Item Location Combination.
        blockConfig_Loca->setTag(CHAR2STR("位置"));
        blockConfig_Loca->setOptionWidget(cBoxLoca);
        blockConfig_Loca->setHint("设置工作路径");
    blockConfig->addItem(blockConfig_Name);
    blockConfig->addItem(blockConfig_Loca);
    blockConfig->tidyItemTags();
}
