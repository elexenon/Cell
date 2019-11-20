// Copyright 2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include <QStylePainter>
#include <QStyleOption>
#include "Headers/Kits/customWidget.h"
#include "Headers/Kits/WindWMAPI.h"

customWidget::customWidget(WIDGET_TYPE type, QWidget *parent):
    QWidget(parent),
    m_type(type)
{
    m_color = QColor(247,247,247);
}

const QColor customWidget::color() const
{
    return m_color;
}

void customWidget::setColor(const QColor color)
{
    m_color = color;
    setStyleSheet(QString("QWidget{background-color:rgb(%1,%2,%3);}").arg(color.red()).arg(color.green()).arg(color.blue()));
}

bool customWidget::nativeEvent(const QByteArray &eventType, void *message, long *result)
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

void customWidget::paintEvent(QPaintEvent *event)
{   if(m_type == WIDGET_TYPE::_CHILD){
        QStylePainter painter(this);
        QStyleOption opt;
        opt.initFrom(this);
        opt.rect = rect();
        painter.drawPrimitive(QStyle::PE_Widget, opt);
        QWidget::paintEvent(event);
    }
}

void customWidget::LoadWinStyle(QWidget *obj)
{
    // Achieve the window drop shadow effect.
    HWND hwnd =  (HWND)obj->winId();
    DWORD style = static_cast<DWORD>(::GetWindowLong(hwnd, GWL_STYLE));
    ::SetWindowLong(hwnd, GWL_STYLE, style | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);
    const MARGINS shadow = { 1, 1, 1, 1 };
    WinDwmapi::instance()->DwmExtendFrameIntoClientArea(HWND(winId()), &shadow);
}
