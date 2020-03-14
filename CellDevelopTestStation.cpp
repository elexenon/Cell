// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include "CellDevelopTestStation.h"
#include "ui_CellDevelopTestStation.h"

#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../../CellCore/CellNamespace.h"
#include "Src/CellUI/CustomBaseWidgets/customOptionBlockItem.h"
#include "Src/CellUI/CustomBaseWidgets/customButton.h"
#include "Src/CellUI/CustomBaseWidgets/customOptionBlock.h"
#include "Src/CellUI/CustomBaseWidgets/ButtonWithText.h"
#include "Src/CellUI/CustomBaseWidgets/ButtonWithIcon.h"
#include "Src/CellUI/CustomBaseWidgets/ButtonWithIconText.h"
#include "Src/CellUI/CustomBaseWidgets/ButtonWithIconTextHint.h"
#include "Src/CellUI/CustomBaseWidgets/customDialogButton.h"
#include "Src/CellUI/CustomBaseWidgets/customSwitch.h"
#include "Src/CellUI/CustomBaseWidgets/Processing.h"
#include "Src/CellUI/CustomBaseWidgets/customNavigator.h"

CellDevelopTestStation::CellDevelopTestStation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CellDevelopTestStation)
{
    ui->setupUi(this);
    setWindowTitle(CHAR2STR("Previewing..."));
    setWindowFlag(Qt::Dialog);

    QComboBox *box = new QComboBox;
    QComboBox *box2 = new QComboBox;
    QComboBox *box3 = new QComboBox;
    QComboBox *box4 = new QComboBox;
    QComboBox *box5 = new QComboBox;

    QComboBox *box6 = new QComboBox;
    QComboBox *box7 = new QComboBox;
    QComboBox *box8 = new QComboBox;
    QComboBox *box9 = new QComboBox;
    QComboBox *box10 = new QComboBox;

    customOptionBlockItem *item = new customOptionBlockItem;
    item->setTag("的的黑洞啊实打实啊都是大大阿德撒旦");
    item->setOptionWidget(box);
    item->setHint("对Cell进行一些事无巨细的超级无敌大设置");

    customOptionBlockItem *item2 = new customOptionBlockItem;
    item2->setTag("自动切换");
    item2->setOptionWidget(box2);
    item2->setHint("对Cell进行一些事无巨细的超级说明");

    customOptionBlockItem *item3 = new customOptionBlockItem;
    item3->setTag("超级无敌自动切换");
    item3->setOptionWidget(box3);
    item3->setHint("对Cell进行一些事无巨细的超级说明啊大大撒旦");

    customOptionBlockItem *item4 = new customOptionBlockItem;
    item4->setTag("设置");
    item4->setOptionWidget(box4);
    item4->setHint("我草泥马");

    customOptionBlockItem *item5 = new customOptionBlockItem;
    item5->setTag("哇哇哇哇哇");
    item5->setOptionWidget(box5);
    item5->setHint("我草泥马马马马马马");

    customOptionBlockItem *item6 = new customOptionBlockItem;
    item6->setTag("哦空破解");
    item6->setOptionWidget(box6);
    item6->setHint("我问嗡嗡嗡");

    customOptionBlockItem *item7 = new customOptionBlockItem;
    item7->setTag("打交道的阿达瓦都请问界外球其额外全额完全");
    item7->setOptionWidget(box7);
    item7->setHint("饿我去恶趣味去");

    customOptionBlockItem *item8 = new customOptionBlockItem;
    item8->setTag("大苏打");
    item8->setOptionWidget(box8);
    item8->setHint("完全");

    customOptionBlockItem *item9 = new customOptionBlockItem;
    item9->setTag("飞机飞机是");
    item9->setOptionWidget(box9);
    item9->setHint("安东尼打烂了看的哪款你多看看的");

    customOptionBlockItem *item10 = new customOptionBlockItem;
    item10->setTag("哇哇哇哇哇");
    item10->setOptionWidget(box10);
    item10->setHint("奥德赛大苏打阿德撒旦撒旦你扩散的扩散的三点三看到你撒");

    customOptionBlock *block1 = new customOptionBlock(CHAR2STR("OptionBlock"), this);
    block1->setBrightDarkColor(Cell::CGL247, Cell::CGL30);
    block1->addItem(item);
    block1->addItem(item2);
    block1->addItem(item3);
    block1->addItem(item4);
    block1->addItem(item5, true);
    block1->addItem(item6);
    block1->addItem(item7);
    block1->addItem(item8);
    block1->addItem(item9);
    block1->addItem(item10);
    block1->tidyItems();

    ButtonWithText *btn1 = new ButtonWithText(customButton::StaticRadius, this);
    btn1->setBrightHoverColor(Cell::CGL218);
    btn1->setDarkHoverColor(Cell::CGL130);
    btn1->setBrightDarkColor(Cell::CGL247, Cell::CGL180);
    btn1->initModules("customTextButton");
    btn1->setFixedSize(200, 81);

    ButtonWithIcon *btn2 = new ButtonWithIcon(customButton::Type::CheckableRadius, this);
    btn2->setBrightCheckedColor(Cell::CGL218);
    btn2->setDarkCheckedColor(Cell::CGL218);
    btn2->setBrightDarkColor(Cell::CGL247, Cell::CGL180);
    btn2->initModules(CHAR2STR("cellLogo32"), 32, 32);
    btn2->setFixedSize(200, 81);
    btn2->drawFocusEdgeOnChecked();

    ButtonWithIconText *btn3 = new ButtonWithIconText(customButton::Type::DynamicRadius, this);
    btn3->setBrightHoveringColor(Cell::CGL255);
    btn3->setDarkHoveringColor(Cell::CGL255);
    btn3->setBrightDarkColor(Cell::CGL218, Cell::CGL70);
    btn3->setAnimationDuration(300);
    btn3->initModules(CHAR2STR("btnNewPJ"), 33, 33, CHAR2STR("带图标和文字的Button"));
    btn3->setFixedSize(250, 81);

    ButtonWithIconTextHint *btn4 = new ButtonWithIconTextHint(customButton::Type::CheckableRadius, this);
    btn4->setBrightCheckedColor(Cell::CGL130);
    btn4->setDarkCheckedColor(Cell::CGL180);
    btn4->setBrightDarkColor(Cell::CGL218, Cell::CGL70);
    btn4->initModules(CHAR2STR("btnOpenPJ"), 33, 33, CHAR2STR("打开项目(O)"), 23, CHAR2STR("打开已有的Cell文档"));
    btn4->setFixedSize(250, 81);

    customDialogButton *customDB = new customDialogButton(CHAR2STR("FUSION"), this);
    customDB->setBrightDarkColor(Cell::CGL247, Cell::CGL30);
    customDB->setFixedWidth(300);

    customSwitch *mSwitch = new customSwitch(this);

    ProcessingWidget *wid = new ProcessingWidget(this);

    customOptionBlock *block2 = new customOptionBlock(CHAR2STR("OptionBlock2"), this);
    block2->setBrightDarkColor(Cell::CGL247, Cell::CGL30);

    customNavigator *nav = new customNavigator(this);
    nav->jointBlock(block1);
    nav->jointBlock(block2);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(block1);
    layout->addWidget(block2);
    layout->addWidget(btn1);
    layout->addWidget(btn2);
    layout->addWidget(btn3);
    layout->addWidget(btn4);
    layout->addWidget(customDB);
    layout->addWidget(mSwitch);
    layout->addWidget(wid);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(nav);
    mainLayout->addLayout(layout);

    setLayout(mainLayout);
}

CellDevelopTestStation::~CellDevelopTestStation()
{
    delete ui;
}
