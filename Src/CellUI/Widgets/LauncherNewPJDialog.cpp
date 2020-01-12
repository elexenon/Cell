// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "LauncherNewPJDialog.h"
#include "ui_launcherNewPJDialog.h"

#include "../CustomBaseWidgets/customFrame.h"
#include "../CustomBaseWidgets/customLabel.h"
#include "../CustomBaseWidgets/customStaticButton.h"
#include "../CustomBaseWidgets/customDynamicButton.h"
#include "NewPJProjectCellPage.h"

#include <QStackedWidget>
#include <QButtonGroup>
//#define CELL_DEBUG
LauncherNewPJDialog::LauncherNewPJDialog(CellUiGlobal::COLOR_SCHEME globalMode,QWidget *parent) :
    customDialog(parent),
    ui(new Ui::LauncherNewPJDialog),
    Tab_Cell(new customStaticButton(this)),
    Tab_Others(new customStaticButton(this)),
    Tab_Empty(new customStaticButton(this)),
    Tab_CPP(new customStaticButton(this)),
    Tab_Py(new customStaticButton(this)),
    frame_titleBar(new customFrame(CellUiConst::QSS_CUSTOMFRAME, this)),
    label_choose(new customLabel(CellUiConst::QSS_CUSTOMLABEL, this)),
    label_project(new customLabel(CellUiConst::QSS_CUSTOMLABEL, this)),
    label_file(new customLabel(CellUiConst::QSS_CUSTOMLABEL, this)),
    Tab_Cell_Label(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT, Tab_Cell)),
    Tab_Others_Label(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT, Tab_Others)),
    Tab_Empty_Label(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT, Tab_Empty)),
    Tab_CPP_Label(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT, Tab_CPP)),
    Tab_Py_Label(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT, Tab_Py)),
    LauncherNewPJ_line_splitter1(new QFrame(this)),
    LauncherNewPJ_line_splitter2(new QFrame(this)),
    Btn_Confirm(new customDynamicButton(this)),
    Btn_Cancel(new customDynamicButton(this)),
    Btn_Confirm_label(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT,Btn_Confirm)),
    Btn_Cancel_label(new customLabel(CellUiConst::QSS_CUSTOMLABEL_TRANSPARENT,Btn_Cancel)),
    cellPage(new NewPJProjectCellPage),
    tabs(new QList<customStaticButton*>),
    m_mode(CellUiGlobal::COLOR_SCHEME::_BRIGHT)
{
    ui->setupUi(this);
    Init();
    if(m_mode != globalMode)
        setColorScheme(globalMode);
}

LauncherNewPJDialog::~LauncherNewPJDialog()
{
    delete ui;
    delete tabs;
}

void LauncherNewPJDialog::Init()
{
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    customDialog::LoadWinStyle(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setColor(CellUiConst::GRAYLEVEL255);

    frame_titleBar->setObjectName(QStringLiteral("frame_titleBar"));
    frame_titleBar->setGeometry(0, 0, this->width(), 45);
    frame_titleBar->setColor(CellUiConst::GRAYLEVEL218);

    label_choose->setObjectName(QStringLiteral("label_choose"));
    label_choose->setGeometry(40, 55, 150, 50);
    label_choose->setText(tr("选择一个模板"));
    label_choose->setFont(QFont("Microsoft YaHei UI Light",15));
    label_choose->setColor(CellUiConst::GRAYLEVEL70);

    LauncherNewPJ_line_splitter1->setObjectName(QString::fromUtf8("LauncherNewPJ_line_splitter1"));
    LauncherNewPJ_line_splitter1->setGeometry(QRect(0, 148, 250, 1));
    LauncherNewPJ_line_splitter1->setStyleSheet("QFrame{color:rgb(180,180,180);}");
    LauncherNewPJ_line_splitter1->setFrameShadow(QFrame::Plain);
    LauncherNewPJ_line_splitter1->setFrameShape(QFrame::HLine);

    label_project->setObjectName(QStringLiteral("label_project"));
    label_project->setGeometry(12, 125, 70, 20);
    label_project->setText(QStringLiteral("项目"));
    label_project->setFont(QFont("Microsoft YaHei UI Light"));
    label_project->setColor(CellUiConst::GRAYLEVEL70);

    Tab_Cell->setObjectName(QStringLiteral("Tab_Cell"));
    Tab_Cell->setBrightModeCheckedUncheckedColor(CellUiConst::GRAYLEVEL247,CellUiConst::GRAYLEVEL255);
    Tab_Cell->setDarkModeCheckedUncheckedColor(CellUiConst::GRAYLEVEL70,CellUiConst::GRAYLEVEL30);
    Tab_Cell->Init();
    Tab_Cell->setGeometry(0, 149, 249, 40);
    Tab_Cell->setCheckable(true);
    Tab_Cell->setChecked(true);
    tabs->append(Tab_Cell);

    Tab_Cell_Label->setObjectName(QStringLiteral("Tab_Cell_Label"));
    Tab_Cell_Label->setGeometry(12, 5, 180, 30);
    Tab_Cell_Label->setText(tr("Cell DeepLearning"));
    Tab_Cell_Label->setFont(QFont("Microsoft YaHei UI Light",11));
    Tab_Cell_Label->setColor(CellUiConst::GRAYLEVEL70);

    Tab_Others->setObjectName(QStringLiteral("Tab_Others"));
    Tab_Others->setBrightModeCheckedUncheckedColor(CellUiConst::GRAYLEVEL247,CellUiConst::GRAYLEVEL255);
    Tab_Others->setDarkModeCheckedUncheckedColor(CellUiConst::GRAYLEVEL70,CellUiConst::GRAYLEVEL30);
    Tab_Others->Init();
    Tab_Others->setGeometry(0, 189, 249, 40);
    Tab_Others->setCheckable(true);
    tabs->append(Tab_Others);

    Tab_Others_Label->setObjectName(QStringLiteral("Tab_Others_Label"));
    Tab_Others_Label->setGeometry(12, 5, 150, 30);
    Tab_Others_Label->setText(tr("地震预测系统"));
    Tab_Others_Label->setFont(QFont("Microsoft YaHei UI Light",11));
    Tab_Others_Label->setColor(CellUiConst::GRAYLEVEL70);

    label_file->setObjectName(QStringLiteral("label_file"));
    label_file->setGeometry(12, 246, 70, 20);
    label_file->setText(QStringLiteral("文件"));
    label_file->setFont(QFont("Microsoft YaHei UI Light",9));
    label_file->setColor(CellUiConst::GRAYLEVEL70);

    LauncherNewPJ_line_splitter2->setObjectName(QString::fromUtf8("LauncherNewPJ_line_splitter2"));
    LauncherNewPJ_line_splitter2->setGeometry(QRect(0, 269, 250, 1));
    LauncherNewPJ_line_splitter2->setStyleSheet("QFrame{color:rgb(180,180,180);}");
    LauncherNewPJ_line_splitter2->setFrameShadow(QFrame::Plain);
    LauncherNewPJ_line_splitter2->setFrameShape(QFrame::HLine);

    Tab_Empty->setObjectName(QStringLiteral("Tab_Empty"));
    Tab_Empty->setBrightModeCheckedUncheckedColor(CellUiConst::GRAYLEVEL247,CellUiConst::GRAYLEVEL255);
    Tab_Empty->setDarkModeCheckedUncheckedColor(CellUiConst::GRAYLEVEL70,CellUiConst::GRAYLEVEL30);
    Tab_Empty->Init();
    Tab_Empty->setGeometry(0, 270, 249, 40);
    Tab_Empty->setCheckable(true);
    tabs->append(Tab_Empty);

    Tab_Empty_Label->setObjectName(QStringLiteral("Tab_Empty_Label"));
    Tab_Empty_Label->setGeometry(12, 5, 150, 30);
    Tab_Empty_Label->setText(tr("空白文件"));
    Tab_Empty_Label->setFont(QFont(QStringLiteral("Microsoft YaHei UI Light"),11));
    Tab_Empty_Label->setColor(CellUiConst::GRAYLEVEL70);

    Tab_CPP->setObjectName(QStringLiteral("Tab_CPP"));
    Tab_CPP->setBrightModeCheckedUncheckedColor(CellUiConst::GRAYLEVEL247,CellUiConst::GRAYLEVEL255);
    Tab_CPP->setDarkModeCheckedUncheckedColor(CellUiConst::GRAYLEVEL70,CellUiConst::GRAYLEVEL30);
    Tab_CPP->Init();
    Tab_CPP->setGeometry(0, 310, 249, 40);
    Tab_CPP->setCheckable(true);
    tabs->append(Tab_CPP);

    Tab_CPP_Label->setObjectName(QStringLiteral("Tab_CPP_Label"));
    Tab_CPP_Label->setGeometry(12, 5, 150, 30);
    Tab_CPP_Label->setText(tr("C++文件"));
    Tab_CPP_Label->setFont(QFont(QStringLiteral("Microsoft YaHei UI Light"),11));
    Tab_CPP_Label->setColor(CellUiConst::GRAYLEVEL70);

    Tab_Py->setObjectName(QStringLiteral("Tab_Py"));
    Tab_Py->setBrightModeCheckedUncheckedColor(CellUiConst::GRAYLEVEL247,CellUiConst::GRAYLEVEL255);
    Tab_Py->setDarkModeCheckedUncheckedColor(CellUiConst::GRAYLEVEL70,CellUiConst::GRAYLEVEL30);
    Tab_Py->Init();
    Tab_Py->setGeometry(0, 350, 249, 40);
    Tab_Py->setCheckable(true);
    tabs->append(Tab_Py);

    Tab_Py_Label->setObjectName(QStringLiteral("Tab_Py_Label"));
    Tab_Py_Label->setGeometry(12, 5, 150, 30);
    Tab_Py_Label->setText(tr("Python文件"));
    Tab_Py_Label->setFont(QFont(QStringLiteral("Microsoft YaHei UI Light"),11));
    Tab_Py_Label->setColor(CellUiConst::GRAYLEVEL70);

    Btn_Confirm->setObjectName(QStringLiteral("Btn_Confirm"));
    Btn_Confirm->setBrightModeEnterLeaveColor(QColor(50,200,230),CellUiConst::GRAYLEVEL218);
    Btn_Confirm->setDarkModeEnterLeaveColor(QColor(50,200,230),CellUiConst::GRAYLEVEL70);
    Btn_Confirm->setAnimationDuration(300);
    Btn_Confirm->Init();
    Btn_Confirm->setGeometry(16, 480, 100, 27);
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
    Btn_Cancel->Init();
    Btn_Cancel->setGeometry(133, 480, 100, 27);
    Btn_Cancel->setCursor(Qt::PointingHandCursor);

    Btn_Cancel_label->setObjectName(QStringLiteral("Btn_Cancel_label"));
    Btn_Cancel_label->setGeometry(34, 2, 50, 20);
    Btn_Cancel_label->setText(tr("取消"));
    Btn_Cancel_label->setFont(QFont(QStringLiteral("Microsoft YaHei UI Light")));
    Btn_Cancel_label->setColor(CellUiConst::GRAYLEVEL70);

    ui->stackedWidget->insertWidget(1, cellPage);
    ui->stackedWidget->setCurrentIndex(1);

    setEventConnections();
}

void LauncherNewPJDialog::setAllTabsUnchecked()
{
    for(auto &e : *tabs)
        e->setChecked(false);
}

void LauncherNewPJDialog::setEventConnections()
{
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
    m_mode = mode;
    emit enableColorScheme(mode);
#ifdef CELL_DEBUG
    qDebug() << "--------------------------";
    qDebug() << "NEWPJDIALOG";
    qDebug() << "setColorScheme()";
    qDebug() << "MODE: " << m_mode;
    qDebug() << "--------------------------";
#endif
    const QColor thisColor = (mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT ? CellUiConst::GRAYLEVEL255 : CellUiConst::GRAYLEVEL30);
    const QColor labelColor = (mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT ? CellUiConst::GRAYLEVEL70 : CellUiConst::GRAYLEVEL255);
    const QColor titleColor = (mode == CellUiGlobal::COLOR_SCHEME::_BRIGHT ? CellUiConst::GRAYLEVEL218 : CellUiConst::GRAYLEVEL45);
    CellUiGlobal::setPropertyAnimation({animi},
                                 "color",
                                 this->color(),
                                 thisColor,
                                 CellUiGlobal::CELL_GLOBALANIMIDURATION,
                                 QEasingCurve::InOutCubic,
                                 {this}, nullptr);
    CellUiGlobal::setPropertyAnimation({animi},
                                 "color",
                                 frame_titleBar->color(),
                                 titleColor,
                                 CellUiGlobal::CELL_GLOBALANIMIDURATION,
                                 QEasingCurve::InOutCubic,
                                 {frame_titleBar}, nullptr);
    CellUiGlobal::setPropertyAnimation({label_choose_animi,label_cell_animi,label_others_animi,
                                      label_confirm_animi,label_cancel_animi,label_empty_animi,
                                      label_cpp_animi,label_py_animi
                                      },
                                     "color",
                                     label_choose->color(),
                                     labelColor,
                                     CellUiGlobal::CELL_GLOBALANIMIDURATION,
                                     QEasingCurve::InOutCubic,
                                 {label_choose,Tab_Cell_Label,Tab_Others_Label,
                                     Tab_Empty_Label,Tab_CPP_Label,Tab_Py_Label,
                                     Btn_Confirm_label,Btn_Cancel_label}, nullptr);
}

void LauncherNewPJDialog::Tab_Cell_clicked()
{
    setAllTabsUnchecked();
    Tab_Cell->setChecked(true);
}

void LauncherNewPJDialog::Tab_Others_clicked()
{
    setAllTabsUnchecked();
    Tab_Others->setChecked(true);
}

void LauncherNewPJDialog::Tab_Empty_clicked()
{
    setAllTabsUnchecked();
    Tab_Empty->setChecked(true);
}

void LauncherNewPJDialog::Tab_CPP_clicked()
{
    setAllTabsUnchecked();
    Tab_CPP->setChecked(true);
}

void LauncherNewPJDialog::Tab_Py_clicked()
{
    setAllTabsUnchecked();
    Tab_Py->setChecked(true);
}

void LauncherNewPJDialog::Btn_Cancel_clicked()
{
    this->close();
}

bool LauncherNewPJDialog::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    return customDialog::nativeEvent(eventType, message, result);
}

void LauncherNewPJDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && event->y() <= 40){
        m_move = true;
        m_startPoint = event->globalPos();
        m_windowPoint = this->frameGeometry().topLeft();
    }
}

void LauncherNewPJDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (m_move && event->buttons() & Qt::LeftButton){
        QPoint relativePos = event->globalPos() - m_startPoint;
        this->move(m_windowPoint + relativePos );
    }
}

void LauncherNewPJDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        m_move = false;
    }
}
