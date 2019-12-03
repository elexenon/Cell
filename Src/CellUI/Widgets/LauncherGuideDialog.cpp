// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include <QPropertyAnimation>
#include <QMouseEvent>
#include "ui_LauncherGuideDialog.h"
#include "LauncherGuideDialog.h"
#include "../CustomBaseWidgets/customFrame.h"
#include "../../CellCore/Kits/StyleSheetLoader.hpp"

LauncherGuideDialog::LauncherGuideDialog(QWidget *parent) :
    customDialog(parent),
    ui(new Ui::LauncherGuideDialog),
    frame_titleBar(new customFrame(Cell_Const::QSS_CUSTOMFRAME, this)),
    m_mode(CellGlobal::COLOR_SCHEME::_BRIGHT)
{
    ui->setupUi(this);
    Init();
}

LauncherGuideDialog::~LauncherGuideDialog()
{
    delete ui;
}

void LauncherGuideDialog::Init()
{
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    customDialog::LoadWinStyle(this);

    ui->stackedWidget->setAutoFillBackground(true);

    ui->pushButton->setParent(this);
    ui->pushButton->setGeometry(640, 420, ui->pushButton->width(), ui->pushButton->height());

    frame_titleBar->setGeometry(0, 0, 781, 51);
    frame_titleBar->setStyleSheet(QStringLiteral("QFrame{background-color:rgb(164, 163, 164);}"));

    ui->label_getStart->setFont(QFont(QStringLiteral("微软雅黑"), 18));   
    ui->label_learn->setFont(QFont(QStringLiteral("微软雅黑"), 9));
    CellGlobal::multiModulesOneStyleSheet({ui->label_getStart,ui->label_learn},QStringLiteral("QLabel{color:#DCDCDC;background-color: transparent;}"));

    ui->checkBox_showUp->setFont(QFont(QStringLiteral("微软雅黑 Light")));
    ui->checkBox_showUp->setStyleSheet(QStringLiteral("QCheckBox{color:#798186;background-color: transparent;}"));

    CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("LauncherGuideCloseBtn_Bright.css"));
    ui->Btn_close->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());
    ui->Btn_close->setFont(QFont(QStringLiteral("微软雅黑")));
}

bool LauncherGuideDialog::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    return customDialog::nativeEvent(eventType, message, result);
}

void LauncherGuideDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && event->y() <= 40){
        m_move = true;
        m_startPoint = event->globalPos();
        m_windowPoint = this->frameGeometry().topLeft();
    }
}

void LauncherGuideDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (m_move && event->buttons() & Qt::LeftButton){
        QPoint relativePos = event->globalPos() - m_startPoint;
        this->move(m_windowPoint + relativePos );
    }
}

void LauncherGuideDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        m_move = false;
    }
}

void LauncherGuideDialog::setColorScheme(CellGlobal::COLOR_SCHEME mode)
{
    if(m_mode == mode) return;
    m_mode = mode;
    const QColor targetColor = (mode == CellGlobal::COLOR_SCHEME::_BRIGHT ? QColor(164,164,164) : Cell_Const::GRAYLEVEL45);
    CellGlobal::setPropertyAnimation({animi_title},
                                 "color",
                                 frame_titleBar->color(),
                                 targetColor,
                                 CellGlobal::CELL_GLOBALANIMIDURATION,
                                 QEasingCurve::InOutCubic,
                                 {frame_titleBar}, nullptr);
    if(mode == CellGlobal::COLOR_SCHEME::_DARK){
        CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("LauncherGuideCloseBtn_Dark.css"));
        ui->Btn_close->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());
    }
    else{
        CellEntityTools::styleSheetLoader->setStyleSheetName(QStringLiteral("LauncherGuideCloseBtn_Bright.css"));
        ui->Btn_close->setStyleSheet(CellEntityTools::styleSheetLoader->styleSheet());
    }
}

void LauncherGuideDialog::on_Btn_close_clicked()
{
    close();
}
static int cnt = 1;
void LauncherGuideDialog::on_pushButton_clicked()
{
    if(cnt == 3) cnt = 0;
    ui->stackedWidget->setCurrentIndex(cnt++);
}
