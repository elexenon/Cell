// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "LauncherNewPJDialog.h"
#include "ui_launcherNewPJDialog.h"

#include "../CustomBaseWidgets/customTitleBar.h"
#include "../CustomBaseWidgets/customLabel.h"
#include "../CustomBaseWidgets/customStaticButton.h"
#include "../CustomBaseWidgets/customListButton.h"
#include "../CustomBaseWidgets/customButtonListWidget.h"
#include "../CustomBaseWidgets/customDynamicButton.h"
#include "NewPJProjectCellPage.h"

#include <QStackedWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QButtonGroup>
#define CELL_DEBUG
LauncherNewPJDialog::LauncherNewPJDialog(CellUiGlobal::COLOR_SCHEME globalMode,QWidget *parent) :
    customWinstyleDialog(parent),
    ui(new Ui::LauncherNewPJDialog),
    titleBar(new customTitleBar(this)),
    label_choose(new customLabel(CellUiConst::QSS_CUSTOMLABEL, this)),
    Btn_Confirm(new customDynamicButton(this)),
    Btn_Cancel(new customDynamicButton(this)),
    Btn_Confirm_label(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT,Btn_Confirm)),
    Btn_Cancel_label(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT,Btn_Cancel)),
    cellPage(new NewPJProjectCellPage),
    BtnListWidget1(new customButtonListWidget(this)),
    BtnListWidget2(new customButtonListWidget(this))
{
    ui->setupUi(this);
    Init();
    if(m_mode != globalMode)
        setColorScheme(globalMode);
}

LauncherNewPJDialog::~LauncherNewPJDialog()
{
    delete ui;
}

void LauncherNewPJDialog::Init()
{
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    customWinstyleDialog::LoadWinStyle(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setBrightDarkModeColor(CellUiConst::GRAYLEVEL255, CellUiConst::GRAYLEVEL30);

    QFont font(QString::fromUtf8("Microsoft YaHei UI Light"));
    font.setPixelSize(15);
    titleBar->setFixedHeight(40);
    titleBar->setBrightDarkModeColor(CellUiConst::GRAYLEVEL218, CellUiConst::GRAYLEVEL45);
    titleBar->setText(QString::fromUtf8("CELL WORKSTATION"), CellUiConst::GRAYLEVEL70);

    font.setPixelSize(25);
    label_choose->setObjectName(QStringLiteral("label_choose"));
    label_choose->setText(tr("选择一个模板"));
    label_choose->setFont(font);
    label_choose->setBrightDarkModeColor(CellUiConst::GRAYLEVEL70, CellUiConst::GRAYLEVEL255);

    font.setPixelSize(18);
    BtnListWidget1->addThemeHead("项目");
    BtnListWidget1->addButton("Cell DeepLearning",CellUiConst::GRAYLEVEL247,CellUiConst::GRAYLEVEL255,CellUiConst::GRAYLEVEL70,CellUiConst::GRAYLEVEL30);
    BtnListWidget1->addButton("地震预测系统",CellUiConst::GRAYLEVEL247,CellUiConst::GRAYLEVEL255,CellUiConst::GRAYLEVEL70,CellUiConst::GRAYLEVEL30);
    BtnListWidget1->setButtonSize(249,40);
    BtnListWidget1->setSpacing(0);
    BtnListWidget1->setFont(font);
    BtnListWidget1->setBrightDarkModeColor(CellUiConst::GRAYLEVEL255,CellUiConst::GRAYLEVEL30);

    BtnListWidget2->addThemeHead("文件");
    BtnListWidget2->addButton("空白文件",CellUiConst::GRAYLEVEL247,CellUiConst::GRAYLEVEL255,CellUiConst::GRAYLEVEL70,CellUiConst::GRAYLEVEL30);
    BtnListWidget2->addButton("C++文件",CellUiConst::GRAYLEVEL247,CellUiConst::GRAYLEVEL255,CellUiConst::GRAYLEVEL70,CellUiConst::GRAYLEVEL30);
    BtnListWidget2->addButton("Python文件",CellUiConst::GRAYLEVEL247,CellUiConst::GRAYLEVEL255,CellUiConst::GRAYLEVEL70,CellUiConst::GRAYLEVEL30);
    BtnListWidget2->setButtonSize(249,40);
    BtnListWidget2->setSpacing(0);
    BtnListWidget2->setFont(font);
    BtnListWidget2->setBrightDarkModeColor(CellUiConst::GRAYLEVEL255,CellUiConst::GRAYLEVEL30);

    Btn_Confirm->setObjectName(QStringLiteral("Btn_Confirm"));
    Btn_Confirm->setBrightModeEnterLeaveColor(QColor(50,200,230),CellUiConst::GRAYLEVEL218);
    Btn_Confirm->setDarkModeEnterLeaveColor(QColor(50,200,230),CellUiConst::GRAYLEVEL70);
    Btn_Confirm->setAnimationDuration(300);
    Btn_Confirm->setFixedSize(100, 27);
    Btn_Confirm->setCursor(Qt::PointingHandCursor);

    Btn_Confirm_label->setObjectName(QStringLiteral("Btn_Confirm_label"));
    Btn_Confirm_label->setGeometry(34, 2, 50, 20);
    Btn_Confirm_label->setText(tr("确认"));
    Btn_Confirm_label->setFont(QFont(QStringLiteral("Microsoft YaHei UI Light")));
    Btn_Confirm_label->setColor(CellUiConst::GRAYLEVEL70);

    Btn_Cancel->setObjectName(QStringLiteral("Btn_Cancel"));
    Btn_Cancel->setBrightModeEnterLeaveColor(QColor(50,200,230),CellUiConst::GRAYLEVEL218);
    Btn_Cancel->setDarkModeEnterLeaveColor(QColor(50,200,230),CellUiConst::GRAYLEVEL70);
    Btn_Cancel->setAnimationDuration(300);
    Btn_Cancel->setFixedSize(100, 27);
    Btn_Cancel->setCursor(Qt::PointingHandCursor);

    Btn_Cancel_label->setObjectName(QStringLiteral("Btn_Cancel_label"));
    Btn_Cancel_label->setGeometry(34, 2, 50, 20);
    Btn_Cancel_label->setText(tr("取消"));
    Btn_Cancel_label->setFont(QFont(QStringLiteral("Microsoft YaHei UI Light")));
    Btn_Cancel_label->setColor(CellUiConst::GRAYLEVEL70);

    QHBoxLayout *HLayout_Bottom = new QHBoxLayout;
    HLayout_Bottom->addWidget(Btn_Confirm);
    HLayout_Bottom->addWidget(Btn_Cancel);
    HLayout_Bottom->setSpacing(17);
    HLayout_Bottom->setMargin(0);

    QHBoxLayout *HLayout_Top = new QHBoxLayout;
    HLayout_Top->addWidget(label_choose);
    HLayout_Top->setAlignment(Qt::AlignmentFlag::AlignHCenter);

    QVBoxLayout *VLayout_left = new QVBoxLayout;
    VLayout_left->addLayout(HLayout_Top);
    VLayout_left->addStretch();
    VLayout_left->addWidget(BtnListWidget1);
    VLayout_left->addWidget(BtnListWidget2);
    VLayout_left->addStretch();
    VLayout_left->addLayout(HLayout_Bottom);
    VLayout_left->setContentsMargins(0, 20, 0, 11);
    VLayout_left->setSpacing(20);

    VLine_Splitter = CellUiGlobal::getLine(CellUiGlobal::LINE_TYPE::VLine);

    QHBoxLayout *HLayout = new QHBoxLayout;
    HLayout->addLayout(VLayout_left);
    HLayout->addWidget(VLine_Splitter);
    HLayout->addWidget(ui->stackedWidget);
    HLayout->setMargin(0);
    HLayout->setSpacing(0);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(titleBar);
    mainLayout->addLayout(HLayout);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    setLayout(mainLayout);

    ui->stackedWidget->insertWidget(1, cellPage);
    ui->stackedWidget->setCurrentIndex(1);

    setEventConnections();
}

void LauncherNewPJDialog::setEventConnections()
{
    const customListButton* Tab_Cell = BtnListWidget1->getButton(0);
    const customListButton* Tab_Others = BtnListWidget1->getButton(1);
    const customListButton* Tab_Empty = BtnListWidget2->getButton(0);
    const customListButton* Tab_CPP = BtnListWidget2->getButton(1);
    const customListButton* Tab_Py = BtnListWidget2->getButton(2);

    connect(Tab_Cell, SIGNAL(clicked(bool)), this, SLOT(Tab_Cell_clicked()));
    connect(Tab_Others, SIGNAL(clicked(bool)), this, SLOT(Tab_Others_clicked()));
    connect(Tab_Empty, SIGNAL(clicked(bool)), this, SLOT(Tab_Empty_clicked()));
    connect(Tab_CPP, SIGNAL(clicked(bool)), this, SLOT(Tab_CPP_clicked()));
    connect(Tab_Py, SIGNAL(clicked(bool)), this, SLOT(Tab_Py_clicked()));
    connect(Btn_Cancel, SIGNAL(clicked(bool)), this, SLOT(Btn_Cancel_clicked()));

    connect(this, SIGNAL(enableColorScheme(COLOR_SCHEME)),Tab_Cell, SLOT(setColorScheme(COLOR_SCHEME)));
    connect(this, SIGNAL(enableColorScheme(COLOR_SCHEME)),Tab_Others, SLOT(setColorScheme(COLOR_SCHEME)));
    connect(this, SIGNAL(enableColorScheme(COLOR_SCHEME)),Tab_Empty, SLOT(setColorScheme(COLOR_SCHEME)));
    connect(this, SIGNAL(enableColorScheme(COLOR_SCHEME)),Tab_CPP, SLOT(setColorScheme(COLOR_SCHEME)));
    connect(this, SIGNAL(enableColorScheme(COLOR_SCHEME)),Tab_Py, SLOT(setColorScheme(COLOR_SCHEME)));
    connect(this, SIGNAL(enableColorScheme(COLOR_SCHEME)),Btn_Confirm, SLOT(setColorScheme(COLOR_SCHEME)));
    connect(this, SIGNAL(enableColorScheme(COLOR_SCHEME)),Btn_Cancel, SLOT(setColorScheme(COLOR_SCHEME)));
}

void LauncherNewPJDialog::setColorScheme(CellUiGlobal::COLOR_SCHEME mode){
    if(mode == m_mode) return;
    emit enableColorScheme(mode);
#ifdef CELL_DEBUG
    qDebug() << "--------------------------";
    qDebug() << "NEWPJDIALOG";
    qDebug() << "setColorScheme()";
    qDebug() << "MODE: " << m_mode;
    qDebug() << "--------------------------";
#endif
    customWinstyleDialog::setColorScheme(mode);
    const QColor labelColor = (mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT ? CellUiConst::GRAYLEVEL70 : CellUiConst::GRAYLEVEL255);  
    CellUiGlobal::setPropertyAnimation({label_choose_animi,
                                      label_confirm_animi,label_cancel_animi},
                                     "color",
                                     label_choose->color(),
                                     labelColor,
                                     CellUiGlobal::CELL_GLOBALANIMIDURATION,
                                     QEasingCurve::InOutCubic,
                                    {label_choose,
                                     Btn_Confirm_label,Btn_Cancel_label}, nullptr);
}

void LauncherNewPJDialog::Tab_Cell_clicked()
{

}

void LauncherNewPJDialog::Tab_Others_clicked()
{

}

void LauncherNewPJDialog::Tab_Empty_clicked()
{

}

void LauncherNewPJDialog::Tab_CPP_clicked()
{

}

void LauncherNewPJDialog::Tab_Py_clicked()
{

}

void LauncherNewPJDialog::Btn_Cancel_clicked()
{
    this->close();
}
