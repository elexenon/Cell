// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "customDialog.h"
#include "../../CellCore/Kits/WindWMAPI.h"

customDialog::customDialog(QWidget *parent):
    QDialog(parent)
{}

void customDialog::setColor(const QColor &color)
{
    CellWidgetGlobalInterface::setColor(color);
    QDialog::setStyleSheet(QString("QDialog{background-color: rgb(%1, %2, %3);}").arg(color.red()).arg(color.green()).arg(color.blue()));
}

void customDialog::LoadWinStyle(QWidget *obj)
{
    HWND hwnd =  (HWND)obj->winId();
    DWORD style = static_cast<DWORD>(::GetWindowLong(hwnd, GWL_STYLE));
    ::SetWindowLong(hwnd, GWL_STYLE, style | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);
    const MARGINS shadow = { 1, 1, 1, 1 };
    WinDwmapi::instance()->DwmExtendFrameIntoClientArea(HWND(winId()), &shadow);
}

bool customDialog::nativeEvent(const QByteArray &eventType, void *message, long *result)
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
