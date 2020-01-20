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
#include "../CustomBaseWidgets/customOptionBlockSector.h"
#include "../CustomBaseWidgets/customOptionBlockItem.h"
#include "LauncherSettings.h"

#include <QPropertyAnimation>
#include <QDebug>
#include <QComboBox>
#include <QVBoxLayout>

LauncherSettings::LauncherSettings(QWidget *parent) :
    customFrame(CellUiConst::QSS_CUSTOMFRAME,parent)
    ,comboBox1(new QComboBox)
    ,comboBox2(new QComboBox)
    ,comboBox3(new QComboBox)
    ,comboBox4(new QComboBox)
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

    using CellEntityTools::styleSheetLoader;
    styleSheetLoader->setStyleSheetName(QStringLiteral("LauncherSettings_OptionBlock1_ComboBox.css"));
    comboBox1->setFixedHeight(30);
    comboBox2->setFixedHeight(30);
    comboBox3->setFixedHeight(30);
    comboBox4->setFixedHeight(30);
    CellUiGlobal::multiModulesOneStyleSheet({comboBox1, comboBox2, comboBox3, comboBox4},
                                            styleSheetLoader->styleSheet());

    itemAppear = new customOptionBlockItem;
    itemAppear->setTag("外观");
    itemAppear->setOptionWidget(comboBox1);
    itemAppear->setHint("调整Cell的工作主题");

    itemAuto = new customOptionBlockItem;
    itemAuto->setTag("自动切换");
    itemAuto->setOptionWidget(comboBox2);
    //itemAuto->setHint("在日落时自动切换工作主题");

    itemPath = new customOptionBlockItem;
    itemPath->setTag("路径");
    itemPath->setOptionWidget(comboBox3);
    itemPath->setHint("设置项目路径");

    itemKit = new customOptionBlockItem;
    itemKit->setTag("工具链");
    itemKit->setOptionWidget(comboBox4);
    itemKit->setHint("设置工具链目录");

    sector1 = new customOptionBlockSector;
    sector1->addItem(itemAppear);
    sector1->addItem(itemAuto);

    sector2 = new customOptionBlockSector;
    sector2->addItem(itemPath);
    sector2->addItem(itemKit);



    blockGeneral = new customOptionBlock(this, CHAR2STR("通用"));
    blockGeneral->setBrightDarkModeColor(CellUiConst::GRAYLEVEL247, CellUiConst::GRAYLEVEL30);
    blockGeneral->addSector(sector1);
    blockGeneral->addSector(sector2, false);
    blockGeneral->tidyItemTags();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setContentsMargins(45, 30, 45, 0);
    layout->addWidget(blockGeneral);
    layout->addStretch();

    setLayout(layout);

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
