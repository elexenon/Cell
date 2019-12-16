// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "launcherNewPJDialog.h"
#include "ui_launcherNewPJDialog.h"

#include "../CustomBaseWidgets/customFrame.h"
#include "../CustomBaseWidgets/customLabel.h"
#include "../CustomBaseWidgets/customStaticButton.h"

#include <QStackedWidget>
//#define CELL_DEBUG
LauncherNewPJDialog::LauncherNewPJDialog(CellGlobal::COLOR_SCHEME globalMode,QWidget *parent) :
    customDialog(parent),
    ui(new Ui::LauncherNewPJDialog),
    Tab_Cell(new customStaticButton(this)),
    Tab_Others(new customStaticButton(this)),
    Tab_Empty(new customStaticButton(this)),
    Tab_CPP(new customStaticButton(this)),
    Tab_Py(new customStaticButton(this)),
    frame_titleBar(new customFrame(Cell_Const::QSS_CUSTOMFRAME, this)),
    label_choose(new customLabel(Cell_Const::QSS_CUSTOMLABEL, this)),
    label_project(new customLabel(Cell_Const::QSS_CUSTOMLABEL, this)),
    label_file(new customLabel(Cell_Const::QSS_CUSTOMLABEL, this)),
    frame_project(new customFrame(Cell_Const::QSS_CUSTOMFRAME, this)),
    frame_file(new customFrame(Cell_Const::QSS_CUSTOMFRAME, this)),
    Tab_Cell_Label(new customLabel(Cell_Const::QSS_CUSTOMLABEL_TRANSPARENT, Tab_Cell)),
    Tab_Others_Label(new customLabel(Cell_Const::QSS_CUSTOMLABEL_TRANSPARENT, Tab_Others)),
    Tab_Empty_Label(new customLabel(Cell_Const::QSS_CUSTOMLABEL_TRANSPARENT, Tab_Empty)),
    Tab_CPP_Label(new customLabel(Cell_Const::QSS_CUSTOMLABEL_TRANSPARENT, Tab_CPP)),
    Tab_Py_Label(new customLabel(Cell_Const::QSS_CUSTOMLABEL_TRANSPARENT, Tab_Py)),
    stackedWidget(new QStackedWidget(this)),
    tabs(new QList<customStaticButton*>),
    m_mode(CellGlobal::COLOR_SCHEME::_BRIGHT)
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

    frame_titleBar->setObjectName(QStringLiteral("frame_titleBar"));
    frame_titleBar->setGeometry(0, 0, 600, 45);
    frame_titleBar->setColor(QColor(164,164,164));

    frame_project->setObjectName(QStringLiteral("frame_project"));
    frame_project->setGeometry(20, 120, 150, 20);
    frame_project->setColor(QColor(50,200,230));

    label_project->setObjectName(QStringLiteral("label_project"));
    label_project->setGeometry(10, 0, 70, 20);
    label_project->setText(QStringLiteral("PROJECT"));
    label_project->setFont(QFont("Microsoft YaHei UI",7,QFont::Bold));
    label_project->setColor(Cell_Const::GRAYLEVEL255);
    label_project->setParent(frame_project);

    label_choose->setObjectName(QStringLiteral("label_choose"));
    label_choose->setGeometry(18, 55, 150, 50);
    label_choose->setText(tr("选择一个模板"));
    label_choose->setFont(QFont("微软雅黑 Light",15));
    label_choose->setColor(Cell_Const::GRAYLEVEL70);

    Tab_Cell->setObjectName(QStringLiteral("Tab_Cell"));
    Tab_Cell->setBrightModeCheckedUncheckedColor(Cell_Const::GRAYLEVEL218,Cell_Const::GRAYLEVEL247);
    Tab_Cell->setDarkModeCheckedUncheckedColor(Cell_Const::GRAYLEVEL70,Cell_Const::GRAYLEVEL30);
    Tab_Cell->Init();
    Tab_Cell->setGeometry(20, 149, 150, 30);
    Tab_Cell->setCheckable(true);
    Tab_Cell->setChecked(true);
    tabs->append(Tab_Cell);

    Tab_Cell_Label->setObjectName(QStringLiteral("Tab_Cell_Label"));
    Tab_Cell_Label->setGeometry(5, 0, 150, 30);
    Tab_Cell_Label->setText(tr("Cell DeepLearning"));
    Tab_Cell_Label->setFont(QFont("微软雅黑 Light",10));
    Tab_Cell_Label->setColor(Cell_Const::GRAYLEVEL70);

    Tab_Others->setObjectName(QStringLiteral("Tab_Others"));
    Tab_Others->setBrightModeCheckedUncheckedColor(Cell_Const::GRAYLEVEL218,Cell_Const::GRAYLEVEL247);
    Tab_Others->setDarkModeCheckedUncheckedColor(Cell_Const::GRAYLEVEL70,Cell_Const::GRAYLEVEL30);
    Tab_Others->Init();
    Tab_Others->setGeometry(20, 182, 150, 30);
    Tab_Others->setCheckable(true);
    tabs->append(Tab_Others);

    Tab_Others_Label->setObjectName(QStringLiteral("Tab_Others_Label"));
    Tab_Others_Label->setGeometry(5, 0, 150, 30);
    Tab_Others_Label->setText(tr("其它"));
    Tab_Others_Label->setFont(QFont("微软雅黑 Light",10));
    Tab_Others_Label->setColor(Cell_Const::GRAYLEVEL70);

    frame_file->setObjectName(QStringLiteral("frame_file"));
    frame_file->setGeometry(20, 222, 150, 20);
    frame_file->setColor(QColor(50,200,230));

    label_file->setObjectName(QStringLiteral("label_file"));
    label_file->setGeometry(10, 0, 70, 20);
    label_file->setText(QStringLiteral("FILE"));
    label_file->setFont(QFont("Microsoft YaHei UI",7,QFont::Bold));
    label_file->setColor(Cell_Const::GRAYLEVEL255);
    label_file->setParent(frame_file);

    Tab_Empty->setObjectName(QStringLiteral("Tab_Empty"));
    Tab_Empty->setBrightModeCheckedUncheckedColor(Cell_Const::GRAYLEVEL218,Cell_Const::GRAYLEVEL247);
    Tab_Empty->setDarkModeCheckedUncheckedColor(Cell_Const::GRAYLEVEL70,Cell_Const::GRAYLEVEL30);
    Tab_Empty->Init();
    Tab_Empty->setGeometry(20, 251, 150, 30);
    Tab_Empty->setCheckable(true);
    tabs->append(Tab_Empty);

    Tab_Empty_Label->setObjectName(QStringLiteral("Tab_Empty_Label"));
    Tab_Empty_Label->setGeometry(5, 0, 150, 30);
    Tab_Empty_Label->setText(tr("空白文件"));
    Tab_Empty_Label->setFont(QFont("微软雅黑 Light",10));
    Tab_Empty_Label->setColor(Cell_Const::GRAYLEVEL70);

    Tab_CPP->setObjectName(QStringLiteral("Tab_CPP"));
    Tab_CPP->setBrightModeCheckedUncheckedColor(Cell_Const::GRAYLEVEL218,Cell_Const::GRAYLEVEL247);
    Tab_CPP->setDarkModeCheckedUncheckedColor(Cell_Const::GRAYLEVEL70,Cell_Const::GRAYLEVEL30);
    Tab_CPP->Init();
    Tab_CPP->setGeometry(20, 284, 150, 30);
    Tab_CPP->setCheckable(true);
    tabs->append(Tab_CPP);

    Tab_CPP_Label->setObjectName(QStringLiteral("Tab_CPP_Label"));
    Tab_CPP_Label->setGeometry(5, 0, 150, 30);
    Tab_CPP_Label->setText(tr("C++文件"));
    Tab_CPP_Label->setFont(QFont("微软雅黑 Light",10));
    Tab_CPP_Label->setColor(Cell_Const::GRAYLEVEL70);

    Tab_Py->setObjectName(QStringLiteral("Tab_Py"));
    Tab_Py->setBrightModeCheckedUncheckedColor(Cell_Const::GRAYLEVEL218,Cell_Const::GRAYLEVEL247);
    Tab_Py->setDarkModeCheckedUncheckedColor(Cell_Const::GRAYLEVEL70,Cell_Const::GRAYLEVEL30);
    Tab_Py->Init();
    Tab_Py->setGeometry(20, 317, 150, 30);
    Tab_Py->setCheckable(true);
    tabs->append(Tab_Py);

    Tab_Py_Label->setObjectName(QStringLiteral("Tab_Py_Label"));
    Tab_Py_Label->setGeometry(5, 0, 150, 30);
    Tab_Py_Label->setText(tr("Python文件"));
    Tab_Py_Label->setFont(QFont("微软雅黑 Light",10));
    Tab_Py_Label->setColor(Cell_Const::GRAYLEVEL70);

    stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
    stackedWidget->setGeometry(190,45,411,355);


    CellGlobal::setDropShadowEffect({eff_dse},
                               {frame_project},
                                QPoint(0,0),QColor(50,200,230),10);

    CellGlobal::setDropShadowEffect({eff_dse},
                               {frame_file},
                                    QPoint(0,0),QColor(50,200,230),10);
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

    connect(this, SIGNAL(enableColorScheme(COLOR_SCHEME)),Tab_Cell, SLOT(setColorScheme(COLOR_SCHEME)));
    connect(this, SIGNAL(enableColorScheme(COLOR_SCHEME)),Tab_Others, SLOT(setColorScheme(COLOR_SCHEME)));
    connect(this, SIGNAL(enableColorScheme(COLOR_SCHEME)),Tab_Empty, SLOT(setColorScheme(COLOR_SCHEME)));
    connect(this, SIGNAL(enableColorScheme(COLOR_SCHEME)),Tab_CPP, SLOT(setColorScheme(COLOR_SCHEME)));
    connect(this, SIGNAL(enableColorScheme(COLOR_SCHEME)),Tab_Py, SLOT(setColorScheme(COLOR_SCHEME)));
}

void LauncherNewPJDialog::setColorScheme(CellGlobal::COLOR_SCHEME mode){
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
    const QColor labelColor = (mode == CellGlobal::COLOR_SCHEME::_BRIGHT ? Cell_Const::GRAYLEVEL70 : Cell_Const::GRAYLEVEL255);
    const QColor titleColor = (mode == CellGlobal::COLOR_SCHEME::_BRIGHT ? QColor(164,164,164) : Cell_Const::GRAYLEVEL45);
    CellGlobal::setPropertyAnimation({animi},
                                 "color",
                                 frame_titleBar->color(),
                                 titleColor,
                                 CellGlobal::CELL_GLOBALANIMIDURATION,
                                 QEasingCurve::InOutCubic,
                                 {frame_titleBar}, nullptr);
    CellGlobal::setPropertyAnimation({label_choose_animi,label_cell_animi,label_others_animi,
                                      label_empty_animi,label_cpp_animi,label_py_animi},
                                     "color",
                                     label_choose->color(),
                                     labelColor,
                                     CellGlobal::CELL_GLOBALANIMIDURATION,
                                     QEasingCurve::InOutCubic,
                                 {label_choose,Tab_Cell_Label,Tab_Others_Label,
                                     Tab_Empty_Label,Tab_CPP_Label,Tab_Py_Label}, nullptr);
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
