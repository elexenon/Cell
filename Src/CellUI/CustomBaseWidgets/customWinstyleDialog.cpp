// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customWinstyleDialog.h"
#include "../../CellCore/Kits/WindWMAPI.h"

customWinstyleDialog::customWinstyleDialog(QWidget *parent):
    QDialog(parent)
{
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
}

void customWinstyleDialog::setColor(const QColor &color)
{
    CellWidgetGlobalInterface::setColor(color);
    QDialog::setStyleSheet(QString("QDialog{background-color: rgb(%1, %2, %3);}").arg(color.red()).arg(color.green()).arg(color.blue()));
}

void customWinstyleDialog::setBaseQss(const QString &qss)
{
    (void)qss;
}

void customWinstyleDialog::changeToColor(const QColor &startColor, const QColor &targetColor, int duration)
{
    CellUiGlobal::setPropertyAnimation({animi},
                                     "color",
                                      startColor,
                                      targetColor,
                                      duration,
                                      easingCurve,
                                      {this}, nullptr);
}

void customWinstyleDialog::LoadWinStyle(QWidget *obj)
{
    HWND hwnd =  (HWND)obj->winId();
    DWORD style = static_cast<DWORD>(::GetWindowLong(hwnd, GWL_STYLE));
    ::SetWindowLong(hwnd, GWL_STYLE, style | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);
    const MARGINS shadow = { 1, 1, 1, 1 };
    WinDwmapi::instance()->DwmExtendFrameIntoClientArea(HWND(winId()), &shadow);
}

void customWinstyleDialog::setColorScheme(CellUiGlobal::COLOR_SCHEME mode)
{
    CellWidgetGlobalInterface::setColorScheme(mode);
}

bool customWinstyleDialog::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG* msg = reinterpret_cast<MSG*>(message);
    switch (msg->message){
        case WM_NCCALCSIZE:{
            *result = 0;
            return true;
        }
        default:
            return QWidget::nativeEvent(eventType, message, result);
    }
}

void customWinstyleDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && event->y() <= 60){
        m_move = true;
        m_startPoint = event->globalPos();
        m_windowPoint = this->frameGeometry().topLeft();
    }
}

void customWinstyleDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (m_move && event->buttons() & Qt::LeftButton){
        QPoint relativePos = event->globalPos() - m_startPoint;
        this->move(m_windowPoint + relativePos );
    }
}

void customWinstyleDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        m_move = false;
    }
}
