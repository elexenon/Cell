#include "CellDevelopTestStation.h"
#include "ui_CellDevelopTestStation.h"

#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "Src/CellUI/CustomBaseWidgets/customOptionBlockItem.h"
#include "Src/CellUI/CustomBaseWidgets/customButton.h"
#include "Src/CellUI/CustomBaseWidgets/customOptionBlockSector.h"
#include "Src/CellUI/CustomBaseWidgets/customOptionBlock.h"

CellDevelopTestStation::CellDevelopTestStation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CellDevelopTestStation)
{
    ui->setupUi(this);
    setWindowTitle(CHAR2STR("Previewing..."));

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

    customOptionBlockSector *sector = new customOptionBlockSector;
    sector->addItem(item);
    sector->addItem(item2);
    sector->addItem(item3, true);




    customOptionBlockItem *item4 = new customOptionBlockItem;
    item4->setTag("设置");
    item4->setOptionWidget(box4);
    item4->setHint("我草泥马");

    customOptionBlockItem *item5 = new customOptionBlockItem;
    item5->setTag("哇哇哇哇哇");
    item5->setOptionWidget(box5);
    item5->setHint("我草泥马马马马马马");

    customOptionBlockSector *sector2 = new customOptionBlockSector;
    sector2->addItem(item4);
    sector2->addItem(item5, true);




    customOptionBlockItem *item6 = new customOptionBlockItem;
    item6->setTag("设置");
    item6->setOptionWidget(box6);
    item6->setHint("我草泥马");

    customOptionBlockItem *item7 = new customOptionBlockItem;
    item7->setTag("哇哇哇哇哇");
    item7->setOptionWidget(box7);
    item7->setHint("我草泥马马马马马马");

    customOptionBlockItem *item8 = new customOptionBlockItem;
    item8->setTag("设置");
    item8->setOptionWidget(box8);
    item8->setHint("我草泥马");

    customOptionBlockItem *item9 = new customOptionBlockItem;
    item9->setTag("哇哇哇哇哇");
    item9->setOptionWidget(box9);
    item9->setHint("我草泥马马马马马马码码码码码码码码码码码码码码");

    customOptionBlockItem *item10 = new customOptionBlockItem;
    item10->setTag("哇哇哇哇哇");
    item10->setOptionWidget(box10);
    item10->setHint("我草泥马马马马马马码码码码码码码码码码码码码码");

    customOptionBlockSector *sector3 = new customOptionBlockSector;
    sector3->addItem(item6);
    sector3->addItem(item7);
    sector3->addItem(item8);
    sector3->addItem(item9);
    sector3->addItem(item10, true);

    customOptionBlock *block1 = new customOptionBlock(this, CHAR2STR("通用"));
    block1->setBrightDarkModeColor(CellUiConst::GRAYLEVEL247, CellUiConst::GRAYLEVEL30);
    block1->addSector(sector);
    block1->addSector(sector2);
    block1->addSector(sector3, true);

    customButton *btn1 = new customButton(customButton::TYPE::STATIC, this);
    btn1->setBrightModeHoverColor(CellUiConst::GRAYLEVEL218);
    btn1->setDarkModeHoverColor(CellUiConst::GRAYLEVEL130);
    btn1->setBrightDarkModeColor(CellUiConst::GRAYLEVEL247, CellUiConst::GRAYLEVEL180);
    btn1->setFixedSize(200, 81);

    customButton *btn3 = new customButton(customButton::TYPE::CHECKABLE, this);
    btn3->setBrightModeCheckedColor(CellUiConst::GRAYLEVEL218);
    btn3->setDarkModeCheckedColor(CellUiConst::GRAYLEVEL130);
    btn3->setBrightDarkModeColor(CellUiConst::GRAYLEVEL247, CellUiConst::GRAYLEVEL180);
    btn3->setFixedSize(200, 81);

    customButton *btn2 = new customButton(customButton::TYPE::DYNAMIC, this);
    btn2->setBrightModeHoveringColor(QColor(50,200,230));
    btn2->setDarkModeHoveringColor(QColor(50,200,230));
    btn2->setBrightDarkModeColor(CellUiConst::GRAYLEVEL218, CellUiConst::GRAYLEVEL180);
    btn2->setAnimationDuration(300);
    btn2->setFixedSize(200, 81);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(block1);
    layout->addWidget(btn1);
    layout->addWidget(btn2);
    layout->addWidget(btn3);

    setLayout(layout);

}

CellDevelopTestStation::~CellDevelopTestStation()
{
    delete ui;
}
