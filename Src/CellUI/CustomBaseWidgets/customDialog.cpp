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

const QColor customDialog::color() const
{
    return m_color;
}

void customDialog::setColor(const QColor &color)
{
    m_color = color;
    setStyleSheet(QString("QWidget{background-color: rgb(%1, %2, %3);}").arg(color.red()).arg(color.green()).arg(color.blue()));
}

#ifdef Q_OS_WIN32
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
#endif

void customDialog::LoadWinStyle(QDialog *obj)
{
#ifdef Q_OS_WIN32
    // Achieve the window drop shadow effect.
    HWND hwnd =  (HWND)obj->winId();
    DWORD style = static_cast<DWORD>(::GetWindowLong(hwnd, GWL_STYLE));
    ::SetWindowLong(hwnd, GWL_STYLE, style | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);
    const MARGINS shadow = { 1, 1, 1, 1 };
    WinDwmapi::instance()->DwmExtendFrameIntoClientArea(HWND(winId()), &shadow);
#endif
}
