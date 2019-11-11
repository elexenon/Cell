// Copyright 2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include <QPropertyAnimation>
#include <QMouseEvent>
#include "Headers/Kits/customFrame.h"
#include "Headers/guidedialog.h"
#include "Headers/Kits/qstylesheetloader.hpp"
#include "ui_guidedialog.h"

using namespace CELL_UTIL;

GuideDialog::GuideDialog(QWidget *parent) :
    customDialog(parent),
    ui(new Ui::GuideDialog),
    frame_titleBar(new customFrame(FRAME_TYPE::_REGULAR, this)),
    m_mode(COLOR_SCHEME::_BRIGHT)
{
    ui->setupUi(this);
    Init();
}

GuideDialog::~GuideDialog()
{
    delete ui;
}

void GuideDialog::Init()
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
    TOOLS::multiModulesOneStyleSheet({ui->label_getStart,ui->label_learn},QStringLiteral("QLabel{color:#DCDCDC;background-color: transparent;}"));

    ui->checkBox_showUp->setFont(QFont(QStringLiteral("微软雅黑 Light")));
    ui->checkBox_showUp->setStyleSheet(QStringLiteral("QCheckBox{color:#798186;background-color: transparent;}"));

    TOOLS::styleSheetLoader->setStyleSheetName(QStringLiteral("GuideDialogCloseBtn_Bright.css"));
    ui->Btn_close->setStyleSheet(TOOLS::styleSheetLoader->styleSheet());
    ui->Btn_close->setFont(QFont(QStringLiteral("微软雅黑")));
}

bool GuideDialog::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    return customDialog::nativeEvent(eventType, message, result);
}

void GuideDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && event->y() <= 40){
        m_move = true;
        m_startPoint = event->globalPos();
        m_windowPoint = this->frameGeometry().topLeft();
    }
}

void GuideDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (m_move && event->buttons() & Qt::LeftButton){
        QPoint relativePos = event->globalPos() - m_startPoint;
        this->move(m_windowPoint + relativePos );
    }
}

void GuideDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        m_move = false;
    }
}

void GuideDialog::setColorScheme(COLOR_SCHEME mode)
{
    if(mode == COLOR_SCHEME::_DARK){
        if(mode == m_mode) return;
        m_mode = COLOR_SCHEME::_DARK;

        TOOLS::styleSheetLoader->setStyleSheetName(QStringLiteral("GuideDialogCloseBtn_Dark.css"));
        ui->Btn_close->setStyleSheet(TOOLS::styleSheetLoader->styleSheet());
        TOOLS::setPropertyAnimation({animi_title}, "color", frame_titleBar->color(), QColor(44, 44, 45), 500,
                             QEasingCurve::InOutCubic, {frame_titleBar}, nullptr);
    }
    else{
        if(mode == m_mode) return;
        m_mode = COLOR_SCHEME::_BRIGHT;

        TOOLS::styleSheetLoader->setStyleSheetName(QStringLiteral("GuideDialogCloseBtn_Bright.css"));
        ui->Btn_close->setStyleSheet(TOOLS::styleSheetLoader->styleSheet());

        TOOLS::setPropertyAnimation({animi_title}, "color", frame_titleBar->color(), QColor(164, 163, 164), 500,
                             QEasingCurve::InOutCubic, {frame_titleBar}, nullptr);
    }
}

void GuideDialog::on_Btn_close_clicked()
{
    close();
}
static int cnt = 1;
void GuideDialog::on_pushButton_clicked()
{
    if(cnt == 3) cnt = 0;
    ui->stackedWidget->setCurrentIndex(cnt++);
}
