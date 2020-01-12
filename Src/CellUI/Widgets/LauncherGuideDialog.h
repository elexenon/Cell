// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef LauncherGuideDialog_H
#define LauncherGuideDialog_H

#include "../../CellCore/Kits/CellUtility.h"    // COLOR_SCHEME
#include "../CustomBaseWidgets/customDialog.h"

class QPropertyAnimation;
class customFrame;

namespace Ui {
class LauncherGuideDialog;
}

class LauncherGuideDialog : public customDialog
{
    Q_OBJECT

public:
    explicit LauncherGuideDialog(QWidget *parent = nullptr);
    ~LauncherGuideDialog();

private:
    Ui::LauncherGuideDialog    *ui;
    customFrame        *frame_titleBar;
    QPropertyAnimation *animi_main;
    QPropertyAnimation *animi_title;

private:
    QPoint  m_startPoint;
    QPoint  m_windowPoint;
    bool    m_move;

private:
    void Init();

private:
    CellUiGlobal::COLOR_SCHEME m_mode;

protected:
#ifdef Q_OS_WIN32
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
#endif

    virtual void mousePressEvent(QMouseEvent *event);

    virtual void mouseMoveEvent(QMouseEvent *event);

    virtual void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void setColorScheme(CellUiGlobal::COLOR_SCHEME);
    void on_Btn_close_clicked();
    void on_pushButton_clicked();
};

#endif // LauncherGuideDialog_H
