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
#include "../CustomBaseWidgets/customDialogButton.h"
#include "../CustomBaseWidgets/customLineEdit.h"
#include "../CustomBaseWidgets/ButtonWithIcon.h"
#include "../../CellCore/CellProjectEntity.h"

#include <QComboBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QFileDialog>

NewPJProjectCellPage::NewPJProjectCellPage(QWidget *parent):
    customFrame(customFrame::_REGULAR, parent)
   ,mainLayout(new QVBoxLayout)
   ,label_title(new customLabel(this))
   ,blockConfig(new customOptionBlock(this, CHAR2STR("项目属性")))
   ,blockConfig_Name(new customOptionBlockItem)
   ,lineEditName(new customLineEdit)
   ,blockConfig_Loca(new customOptionBlockItem)
   ,dialogButton(new customDialogButton(CHAR2STR("Location")))
   ,buttonForward(new ButtonWithIcon(customButton::STATIC, this))
{
    Init();
    setEventConnections();
}

void NewPJProjectCellPage::Init()
{
    setBrightDarkModeColor(CellUiConst::GRAYLEVEL247, CellUiConst::GRAYLEVEL30);
    setLayout(mainLayout);

    buttonForward->setBrightModeHoverColor(CellUiConst::GRAYLEVEL218);
    buttonForward->setDarkModeHoverColor(CellUiConst::GRAYLEVEL180);
    buttonForward->setBrightDarkModeColor(CellUiConst::GRAYLEVEL247, CellUiConst::GRAYLEVEL45);
    buttonForward->Init(CHAR2STR("iconForward"), 20, 15);
    buttonForward->setFixedSize(50, 35);

    QHBoxLayout *HLayoutButtom = new QHBoxLayout;
    HLayoutButtom->addWidget(buttonForward);
    HLayoutButtom->setAlignment(Qt::AlignmentFlag::AlignRight);

    mainLayout->setContentsMargins(50, 20, 50, 10);
    mainLayout->addWidget(label_title);
    mainLayout->addStretch(1);
    mainLayout->addWidget(blockConfig);
    mainLayout->addStretch(6);
    mainLayout->addLayout(HLayoutButtom);

    using CellEntityTools::styleSheetLoader;

    CellUiGlobal::setCustomTextLabel(label_title, CHAR2STR("Microsoft YaHei UI Light"), 24, CHAR2STR("连接到Cell运算库。"));

    lineEditName->setFixedWidth(200);

    dialogButton->setBrightDarkModeColor(CellUiConst::GRAYLEVEL255, CellUiConst::GRAYLEVEL45);
    dialogButton->setFixedWidth(200);

    // OptionBlock Configuration Combination.
    blockConfig->setBrightDarkModeColor(CellUiConst::GRAYLEVEL247, CellUiConst::GRAYLEVEL30);
        // Item Name Combination.
        blockConfig_Name->setTag(CHAR2STR("名称"));
        blockConfig_Name->setOptionWidget(lineEditName);
        blockConfig_Name->setHint("设置项目名称");
        // Item Location Combination.
        blockConfig_Loca->setTag(CHAR2STR("位置"));
        blockConfig_Loca->setOptionWidget(dialogButton);
        blockConfig_Loca->setHint("设置工作路径");
    blockConfig->addItem(blockConfig_Name);
    blockConfig->addItem(blockConfig_Loca);
    blockConfig->tidyItemTags();
}

void NewPJProjectCellPage::setEventConnections()
{
    const ButtonWithIcon* btn = dialogButton->getTrigger();
    connect(btn, &QPushButton::clicked, this, &NewPJProjectCellPage::BtnNameClicked);
}

void NewPJProjectCellPage::BtnNameClicked()
{
    path = QFileDialog::getExistingDirectory(this,
                                             CHAR2STR("选择目录"),
                                             CHAR2STR("C:\\"),
                                             QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    qDebug() << CHAR2STR("Choose Path:") << path;
}

void NewPJProjectCellPage::BtnForwardClicked()
{
    name = lineEditName->text().trimmed();
    emit setProjectDone(name, path);
    qDebug() << CHAR2STR("Project Name:") << name;
}
