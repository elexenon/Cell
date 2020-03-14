// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "newPJPageBase.h"

#include "../../CellCore/CellProjectEntity.h"
#include "../../CellCore/CellNamespace.h"
#include "../../CellCore/Kits/CellUtility.h"
#include "../CustomBaseWidgets/customLabel.h"
#include "../CustomBaseWidgets/customOptionBlock.h"
#include "../CustomBaseWidgets/customOptionBlockItem.h"
#include "../CustomBaseWidgets/customDialogButton.h"
#include "../CustomBaseWidgets/customLineEdit.h"

#include <QComboBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QFileDialog>

newPJPageBase::newPJPageBase(QWidget *parent):
    customFrame(customFrame::Type::Regular, parent),
    mainLayout(new QVBoxLayout(this)),
    labelTitle(new customLabel(this)),
    blockConfig(new customOptionBlock(CHAR2STR("项目属性"), this)),
    lineEditName(new customLineEdit),
    dialogButton(new customDialogButton(CHAR2STR("选择一个目录")))
{
    init();
    setEventConnections();
}

void newPJPageBase::init(){
    setBrightDarkColor(Cell::CGL247, Cell::CGL30);
    setLayout(mainLayout);

    mainLayout->setContentsMargins(60, 20, 60, 10);
    mainLayout->addWidget(labelTitle);
    mainLayout->addStretch(5);
    mainLayout->addWidget(blockConfig);
    mainLayout->addStretch(8);

    labelTitle->setBrightDarkColor(Cell::CGL70, Cell::CGL255);
    CellUiGlobal::setCustomTextLabel(labelTitle, CHAR2STR("Microsoft YaHei UI Light"), 24, CHAR2STR("Title"));

    lineEditName->setFixedWidth(200);

    dialogButton->setBrightDarkColor(Cell::CGL255, Cell::CGL45);
    dialogButton->setFixedWidth(200);

    // OptionBlock Configuration Combination.
    blockConfig->setBrightDarkColor(Cell::CGL247, Cell::CGL30);
    blockConfig->addItem(lineEditName, CHAR2STR("名称"), CHAR2STR("设置项目名称"));
    blockConfig->addItem(dialogButton, CHAR2STR("位置"), CHAR2STR("设置工作路径"));
    blockConfig->tidyItems();

    CellWidgetGlobalInterface::_modules << dialogButton << labelTitle << blockConfig;
}

void newPJPageBase::setEventConnections()
{
    connect(dialogButton, &customDialogButton::clicked, this, &newPJPageBase::btnPathClicked);
    connect(lineEditName, &QLineEdit::textChanged, [this](const QString& text){
        emit nameSettled(text);
    });
}

void newPJPageBase::btnPathClicked()
{
    path = QFileDialog::getExistingDirectory(this,
                                             CHAR2STR("选择目录"),
                                             CHAR2STR("C:\\"),
                                             QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    dialogButton->setText(path);
    emit pathSettled(path);
}

void newPJPageBase::setPageTitle(const QString &text){
    labelTitle->setText(text);
}

void newPJPageBase::addOptionBlock(customOptionBlock *block){
    mainLayout->addWidget(block);
    mainLayout->addStretch(8);
}

void newPJPageBase::enableToolChainsBlock()
{
    blockToolChain = new customOptionBlock(CHAR2STR("ToolChains"), this);
    cBoxVersions = new QComboBox;

    // OptionBlock ToolChains Combination.
    cBoxVersions->addItem("1.0.1");
    blockToolChain->setBrightDarkColor(Cell::CGL247, Cell::CGL30);
    blockToolChain->addItem(cBoxVersions, CHAR2STR("Cell Calculations版本"), CHAR2STR("选择工具链版本"));

    addOptionBlock(blockToolChain);

    CellWidgetGlobalInterface::_modules << blockToolChain;
}
