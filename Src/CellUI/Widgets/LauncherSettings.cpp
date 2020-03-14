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
#include "../CustomBaseWidgets/customNavigator.h"
#include "../Widgets/Launcher.h"
#include "LauncherSettings.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QJsonDocument>
#include <QJsonObject>

const QString LauncherSettings::path("CWS64.json");

LauncherSettings::LauncherSettings(QWidget *parent) :
    customFrame(customFrame::Type::Regular, parent),
    mainLayout(new QHBoxLayout(this)),
    VLayoutRight(new QVBoxLayout),
    navigator(new customNavigator(this, true)),
    blockGeneral(new customOptionBlock(CHAR2STR("通用"), this)),
    dBtnAppear(new customDialogButton(CHAR2STR("FUSION"))),
    switchAuto(new customSwitch),
    switchAbate(new customSwitch),
    dBtnLan(new customDialogButton(CHAR2STR("CHN"))),
    blockWorkshop(new customOptionBlock(CHAR2STR("Workshop"), this)),
    switchMulti(new customSwitch),
    launcherPtr(nullptr)
{
    init();
    loadFile();
}

LauncherSettings::~LauncherSettings()
{
    saveFile();
}

void LauncherSettings::LauncherSetColorSchemeModeCall(Cell::ColorScheme mode)
{
    if(mode == Cell::ColorScheme::Bright){
        btnBrightClicked();
    }else{
        btnDarkClicked();
    }
}

void LauncherSettings::init()
{
    setBrightDarkColor(Cell::CGL247,Cell::CGL45);
    setLayout(mainLayout);

    VLayoutRight->setSpacing(50);
    VLayoutRight->setContentsMargins(45, 0, 45, 0);
    VLayoutRight->addWidget(blockGeneral);
    VLayoutRight->addWidget(blockWorkshop);
    VLayoutRight->addStretch();

    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(0, 30, 0, 0);
    mainLayout->addWidget(navigator);
    mainLayout->addLayout(VLayoutRight);

    // OptionBlock General Combination.
    dBtnAppear->setBrightDarkColor(Cell::CGL247, Cell::CGL100);
    dBtnAppear->setFixedWidth(200);
    dBtnLan->setBrightDarkColor(Cell::CGL247, Cell::CGL100);
    dBtnLan->setFixedWidth(200);
    blockGeneral->setBrightDarkColor(Cell::CGL247, Cell::CGL45);
    blockGeneral->addItem(dBtnAppear, CHAR2STR("外观"), CHAR2STR("调整Cell的工作主题"));
    blockGeneral->addItem(switchAbate, CHAR2STR("削弱动态效果"), CHAR2STR("选择此项可提升部分运行时性能"));
    blockGeneral->addItem(switchAuto, CHAR2STR("自动切换"), CHAR2STR("在日落时自动切换工作主题"), true);
    blockGeneral->addItem(dBtnLan, CHAR2STR("语言"), CHAR2STR("设置全局语言"));

    // OptionBlock Workshop Combination.
    blockWorkshop->setBrightDarkColor(Cell::CGL247, Cell::CGL45);
    blockWorkshop->addItem(switchMulti, CHAR2STR("多实例"), CHAR2STR("允许多个Workshop实例同时存在"));
    blockWorkshop->tidyItems(blockGeneral);

    navigator->setBrightDarkColor(this->brightColor(), this->darkColor());
    navigator->jointBlock(blockGeneral);
    navigator->jointBlock(blockWorkshop);

    CellWidgetGlobalInterface::_modules << dBtnAppear << dBtnLan
             << blockGeneral
             << blockWorkshop << navigator;

    setEventConnections();
}

void LauncherSettings::setEventConnections()
{
    const ButtonWithIcon *trigger1 = dBtnAppear->getTrigger();
    const ButtonWithIcon *trigger2 = dBtnLan->getTrigger();
    connect(trigger1, &QPushButton::clicked, this, &LauncherSettings::btnColorSchemeClicked);
    connect(trigger2, &QPushButton::clicked, this, &LauncherSettings::btnLanguageClicked);
    connect(switchAuto, &customSwitch::clicked, [=](bool checked){
        write(SaveAttribute::Auto, checked == true ? CHAR2STR("true") : CHAR2STR("false"));
        CellWidgetGlobalInterface::autoSwitch = checked == true ? true : false;
    });
    connect(switchAbate, &customSwitch::clicked, [=](bool checked){
        write(SaveAttribute::AbateEffect, checked == true ? CHAR2STR("true") : CHAR2STR("false"));
        CellWidgetGlobalInterface::switchMode = checked == true ? Cell::SwitchMode::Instant : Cell::SwitchMode::OnGoing;
    });
    connect(switchMulti, &customSwitch::clicked,[=](bool checked){
        write(SaveAttribute::MultiInstance, checked == true ? CHAR2STR("true") : CHAR2STR("false"));
    });
}

void LauncherSettings::btnColorSchemeClicked()
{
    static bool statusBright = true;
    statusBright = !statusBright;
    statusBright ? btnBrightClicked() : btnDarkClicked();
    dBtnAppear->setText(statusBright ? CHAR2STR("FUSION") : CHAR2STR("DARK"));
}

void LauncherSettings::btnLanguageClicked()
{
    customMaskDialog *maskDialog = new customMaskDialog(launcherPtr);
    maskDialog->setOptionText(CHAR2STR("语言"));
    maskDialog->setHintText(CHAR2STR("选择全局语言。"));
    maskDialog->setGeometry(launcherPtr->maskGeometry());
    maskDialog->show();
}

void LauncherSettings::initsettingsObj()
{
    QJsonObject tmp;
    tmp["Appearance"] = "FUSION";
    tmp["AutoChange"] = "false";
    tmp["AbateEffect"]= "false";
    tmp["Language"]   = "CHN";
    tmp["MultiInstance"] = "true";
    tmp["OnShowGuideDialog"] = "true";

    settingsObj["CellLauncherSettgins"] = tmp;
    read(tmp);
}

void LauncherSettings::write(LauncherSettings::SaveAttribute key, const QString &value)
{
    QJsonObject tmp = settingsObj["CellLauncherSettgins"].toObject();
    switch(key){
    case Auto:
        tmp["AutoChange"] = value;
        break;
    case AbateEffect:
        tmp["AbateEffect"]= value;
        break;
    case MultiInstance:
        tmp["MultiInstance"] = value;
        break;
    case onShowGuideDialog:
        tmp["OnShowGuideDialog"] = value;
        break;
    }
    settingsObj["CellLauncherSettgins"] = tmp;
}

void LauncherSettings::loadFile()
{
#ifdef CELL_DEBUG
       CELL_DEBUG("LauncherSettings") << "Start Fetching Settings From::" << path << endl;
#endif

       QFile loadFile(path);

    if(!QFileInfo(path).isFile()){
#ifdef CELL_DEBUG
       CELL_DEBUG("LauncherSettings") << "Settings File Not Exists." << endl;
       CELL_DEBUG("LauncherSettings") << "Then create a new one as::" << path << endl;
#endif
        initsettingsObj();
        if(!loadFile.open(QIODevice::WriteOnly))
            qWarning("Couldn't open save file.");
        loadFile.write(QJsonDocument(settingsObj).toJson());
        loadFile.close();
        return;
    }

    if (!loadFile.open(QIODevice::ReadOnly))
        qWarning("Couldn't open save file.");

    QByteArray saveData = loadFile.readAll();
    settingsObj = QJsonDocument::fromJson(saveData).object();
    loadFile.close();

    read(settingsObj["CellLauncherSettgins"].toObject());
}

void LauncherSettings::saveFile()
{
    QFile saveFile(path);
    if (!saveFile.open(QIODevice::WriteOnly))
        qWarning("Couldn't open save file.");
    saveFile.write(QJsonDocument(settingsObj).toJson());
    saveFile.close();
}

void LauncherSettings::read(const QJsonObject &json)
{
    if(json["AbateEffect"] == CMPSTR("true")){
        switchAbate->setChecked(true);
        CellWidgetGlobalInterface::switchMode = Cell::SwitchMode::Instant;
    }else{
        switchAbate->setChecked(false);
        CellWidgetGlobalInterface::switchMode = Cell::SwitchMode::OnGoing;
    }

    if(json["AutoChange"] == CMPSTR("true")){
        switchAuto->setChecked(true);
        CellWidgetGlobalInterface::autoSwitch = true;
    }else{
        switchAuto->setChecked(false);
        CellWidgetGlobalInterface::autoSwitch = false;
    }
    // TODO
    if(json["MultiInstance"] == CMPSTR("true")){
        switchMulti->setChecked(true);
    }else{
        switchMulti->setChecked(false);
    }

    /* TODO
    switch(json["Language"]){

    }*/
    switchAuto->setChecked(json["AutoChange"] == CMPSTR("true") ? true : false);
    switchAbate->setChecked(json["AbateEffect"] == CMPSTR("true") ? true : false);
    switchMulti->setChecked(json["MultiInstance"] == CMPSTR("true") ? true : false);
}

void LauncherSettings::btnBrightClicked()
{
    setColorScheme(Cell::ColorScheme::Bright);
    emit enableColorScheme(Cell::ColorScheme::Bright);
}

void LauncherSettings::btnDarkClicked()
{
    setColorScheme(Cell::ColorScheme::Dark);
    emit enableColorScheme(Cell::ColorScheme::Dark);
}
