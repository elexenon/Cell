// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "../../CellCore/CellNamespace.h"
#include "../CustomBaseWidgets/customFrame.h"
#include "../CustomBaseWidgets/customLabel.h"
#include "../CustomBaseWidgets/customOptionBlock.h"
#include "../CustomBaseWidgets/customOptionBlockItem.h"
#include "../CustomBaseWidgets/customDialogButton.h"
#include "../CustomBaseWidgets/customButton.h"
#include "../CustomBaseWidgets/customMaskDialog.h"
#include "../CustomBaseWidgets/ButtonWithIcon.h"
#include "../CustomBaseWidgets/customSwitch.h"
#include "../Widgets/Launcher.h"
#include "LauncherSettings.h"

#include <QVBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>

#define DEBUG

LauncherSettings::LauncherSettings(QWidget *parent) :
    customFrame(customFrame::_REGULAR, parent),
    mainLayout(new QVBoxLayout(this)),
    blockGeneral(new customOptionBlock(this, CHAR2STR("通用"))),
    blockGeneralItemAppear(new customOptionBlockItem),
    dBtnAppear(new customDialogButton(CHAR2STR("外观"))),
    blockGeneralItemAuto(new customOptionBlockItem),
    switchAuto(new customSwitch),
    blockGeneralItemLan(new customOptionBlockItem),
    dBtnLan(new customDialogButton(CHAR2STR("简体中文"))),
    blockWorkshop(new customOptionBlock(this, CHAR2STR("Workshop"))),
    blockWorkshopItemMulti(new customOptionBlockItem),
    switchMulti(new customSwitch),
    launcherPtr(nullptr)
{
    init();
}

void LauncherSettings::LauncherSetColorSchemeModeCall(CellUiGlobal::COLOR_SCHEME mode)
{
    if(mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT){
        Btn_bright_clicked();
    }else{
        Btn_dark_clicked();
    }
}

void LauncherSettings::init()
{
    setBrightDarkModeColor(Cell::CGL247,Cell::CGL45);
    setLayout(mainLayout);
    mainLayout->setSpacing(50);
    mainLayout->setContentsMargins(45, 30, 45, 0);
    mainLayout->addWidget(blockGeneral);
    mainLayout->addWidget(blockWorkshop);
    mainLayout->addStretch();

    switchMulti->setChecked(true);
    // ComboBox Appear Combination
    dBtnAppear->setBrightDarkModeColor(Cell::CGL247, Cell::CGL30);
    dBtnAppear->setFixedWidth(200);
    // ComboBox Lan Combination.
    dBtnLan->setBrightDarkModeColor(Cell::CGL247, Cell::CGL30);
    dBtnLan->setFixedWidth(200);

    // OptionBlock General Combination.
    blockGeneral->setBrightDarkModeColor(Cell::CGL247, Cell::CGL30);
    // Item Appear Combination.
    blockGeneralItemAppear->setTag("外观");
    blockGeneralItemAppear->setOptionWidget(dBtnAppear);
    blockGeneralItemAppear->setHint("调整Cell的工作主题");
    // Item Auto   Combination.
    blockGeneralItemAuto->setTag("自动切换");
    blockGeneralItemAuto->setOptionWidget(switchAuto);
    blockGeneralItemAuto->setHint("在日落时自动切换工作主题");
    // Item Lan Combination.
    blockGeneralItemLan->setTag("语言");
    blockGeneralItemLan->setOptionWidget(dBtnLan);
    blockGeneralItemLan->setHint("设置全局语言");
    blockGeneral->addItem(blockGeneralItemAppear);
    blockGeneral->addItem(blockGeneralItemAuto, true);
    blockGeneral->addItem(blockGeneralItemLan);

    // OptionBlock Workshop Combination.
    blockWorkshop->setBrightDarkModeColor(Cell::CGL247, Cell::CGL30);
    // Item Multi Combination.
    blockWorkshopItemMulti->setTag("多实例");
    blockWorkshopItemMulti->setOptionWidget(switchMulti);
    blockWorkshopItemMulti->setHint("允许多个Workshop实例同时存在");
    blockWorkshop->addItem(blockWorkshopItemMulti);
    blockWorkshop->tidyItems(blockGeneral);

    setEventConnections();
}

void LauncherSettings::setColorScheme(CellUiGlobal::COLOR_SCHEME mode)
{
    customFrame::setColorScheme(mode);
}

void LauncherSettings::setEventConnections()
{
    const ButtonWithIcon *trigger = dBtnAppear->getTrigger();
    connect(trigger, &QPushButton::clicked, this, &LauncherSettings::btnColorSchemeClicked);

    connect(switchAuto, &customSwitch::clicked, this, &LauncherSettings::switchAutoClicked);
}

void LauncherSettings::btnColorSchemeClicked()
{
    customMaskDialog *maskDialog = new customMaskDialog(launcherPtr);
    maskDialog->setOptionText(CHAR2STR("颜色模式"));
    maskDialog->setHintText(CHAR2STR("选择一个你偏好的颜色模式，Cell会为你自动切换。"));
    maskDialog->setGeometry(launcherPtr->maskGeometry());
    maskDialog->show();
}

void LauncherSettings::write(LauncherSettings::SaveAttribute value)
{

}

void LauncherSettings::read(LauncherSettings::SaveAttribute value)
{

}


void LauncherSettings::switchAutoClicked()
{

}

void LauncherSettings::switchMultiClicked()
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
