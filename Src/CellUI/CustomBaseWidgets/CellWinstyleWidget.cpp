// Copyright 2018-2020 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include "../CustomBaseWidgets/CellWinstyleWidget.h"
#include "../../CellCore/Kits/WindWMAPI.h"

CellWinstyleWidget::CellWinstyleWidget(QWidget *parent):
    QWidget(parent)
{}

void CellWinstyleWidget::LoadWinStyle(QWidget *obj)
{
    // Achieve the window drop shadow effect.
    HWND hwnd =  (HWND)obj->winId();
    DWORD style = static_cast<DWORD>(::GetWindowLong(hwnd, GWL_STYLE));
    ::SetWindowLong(hwnd, GWL_STYLE, style | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);
    const MARGINS shadow = { 1, 1, 1, 1 };
    WinDwmapi::instance()->DwmExtendFrameIntoClientArea(HWND(winId()), &shadow);
}

bool CellWinstyleWidget::nativeEvent(const QByteArray &eventType, void *message, long *result)
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
