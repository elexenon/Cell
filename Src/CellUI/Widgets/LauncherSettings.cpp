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

const QString LauncherSettings::path("CWS64.json");

LauncherSettings::LauncherSettings(QWidget *parent) :
    customFrame(customFrame::Type::Regular, parent),
    mainLayout(new QVBoxLayout(this)),
    blockGeneral(new customOptionBlock(this, CHAR2STR("通用"))),
    blockGeneralItemAppear(new customOptionBlockItem),
    dBtnAppear(new customDialogButton(CHAR2STR("外观"))),
    blockGeneralItemAuto(new customOptionBlockItem),
    switchAuto(new customSwitch),
    blockGeneralItemLan(new customOptionBlockItem),
    dBtnLan(new customDialogButton(CHAR2STR("CHN"))),
    blockWorkshop(new customOptionBlock(this, CHAR2STR("Workshop"))),
    blockWorkshopItemMulti(new customOptionBlockItem),
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
    customFrame::init();
    setBrightDarkColor(Cell::CGL247,Cell::CGL45);
    setLayout(mainLayout);
    mainLayout->setSpacing(50);
    mainLayout->setContentsMargins(45, 30, 45, 0);
    mainLayout->addWidget(blockGeneral);
    mainLayout->addWidget(blockWorkshop);
    mainLayout->addStretch();

    switchMulti->setChecked(true);
    // ComboBox Appear Combination
    dBtnAppear->setBrightDarkColor(Cell::CGL247, Cell::CGL100);
    dBtnAppear->setFixedWidth(200);
    // ComboBox Lan Combination.
    dBtnLan->setBrightDarkColor(Cell::CGL247, Cell::CGL100);
    dBtnLan->setFixedWidth(200);

    // OptionBlock General Combination.
    blockGeneral->setBrightDarkColor(Cell::CGL247, Cell::CGL45);
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
    blockWorkshop->setBrightDarkColor(Cell::CGL247, Cell::CGL45);
    // Item Multi Combination.
    blockWorkshopItemMulti->setTag("多实例");
    blockWorkshopItemMulti->setOptionWidget(switchMulti);
    blockWorkshopItemMulti->setHint("允许多个Workshop实例同时存在");
    blockWorkshop->addItem(blockWorkshopItemMulti);
    blockWorkshop->tidyItems(blockGeneral);

    _modules << dBtnAppear << dBtnLan
             << blockGeneral
             << blockGeneralItemAuto
             << blockWorkshop;

    setEventConnections();
}

void LauncherSettings::setEventConnections()
{
    const ButtonWithIcon *trigger1 = dBtnAppear->getTrigger();
    const ButtonWithIcon *trigger2 = dBtnLan->getTrigger();
    connect(trigger1, &QPushButton::clicked, this, &LauncherSettings::btnColorSchemeClicked);
    connect(trigger2, &QPushButton::clicked, this, &LauncherSettings::btnLanguageClicked);

    connect(switchAuto, &customSwitch::clicked, this, &LauncherSettings::switchAutoClicked);
    connect(switchMulti, &customSwitch::clicked, this, &LauncherSettings::switchMultiClicked);
}

void LauncherSettings::btnColorSchemeClicked()
{
    static bool statusBright = true;
    statusBright = !statusBright;

    statusBright ? btnBrightClicked() : btnDarkClicked();
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
    tmp["Language"]   = "CHN";
    tmp["MultiInstance"] = "true";;

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
    case MultiInstance:
        tmp["MultiInstance"] = value;
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
    if(json["Appearance"] == CMPSTR("FUSION")){

    }else{

    }
    /* TODO
    switch(json["Language"]){

    }*/
    switchAuto->setChecked(json["AutoChange"] == CMPSTR("true") ? true : false);
    switchMulti->setChecked(json["MultiInstance"] == CMPSTR("true") ? true : false);
}

void LauncherSettings::switchAutoClicked(bool checked)
{
    write(SaveAttribute::Auto, checked == true ? CHAR2STR("true") : CHAR2STR("false"));
}

void LauncherSettings::switchMultiClicked(bool checked)
{
    write(SaveAttribute::MultiInstance, checked == true ? CHAR2STR("true") : CHAR2STR("false"));
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
