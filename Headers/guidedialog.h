// Copyright 2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef GUIDEDIALOG_H
#define GUIDEDIALOG_H

#include "Kits/cell_util.h"
#include "Kits/DropShadowDialog.h"

class QPropertyAnimation;
class customFrame;

namespace Ui {
class GuideDialog;
}

class GuideDialog : public DropShadowDialog
{
    Q_OBJECT

public:
    explicit GuideDialog(QWidget *parent = nullptr);
    ~GuideDialog();

private:
    Ui::GuideDialog    *ui;
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
    COLOR_SCHEME m_mode;

protected:
#ifdef Q_OS_WIN32
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
#endif

    virtual void    mousePressEvent(QMouseEvent *event);

    virtual void    mouseMoveEvent(QMouseEvent *event);

    virtual void    mouseReleaseEvent(QMouseEvent *event);
private slots:
    void setColorScheme(COLOR_SCHEME);
    void on_Btn_close_clicked();
    void on_pushButton_clicked();
};

#endif // GUIDEDIALOG_H
