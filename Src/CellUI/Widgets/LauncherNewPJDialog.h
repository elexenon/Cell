// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef LAUNCHERNEWPJDIALOG_H
#define LAUNCHERNEWPJDIALOG_H

#include <QDialog>

#include "../../CellCore/Kits/CellUtility.h"    // COLOR_SCHEME
#include "../CustomBaseWidgets/customDialog.h"

class customFrame;
class customLabel;
class QPropertyAnimation;
class QGraphicsDropShadowEffect;
class customStaticButton;
class QStackedWidget;
class QFrame;
class customDynamicButton;
class NewPJProjectCellPage;
class customButtonListWidget;

namespace Ui {
class LauncherNewPJDialog;
}

class LauncherNewPJDialog : public customDialog
{
    Q_OBJECT

public:
    explicit LauncherNewPJDialog(CellUiGlobal::COLOR_SCHEME globalMode,QWidget *parent = nullptr);
    ~LauncherNewPJDialog();

private:
    Ui::LauncherNewPJDialog *ui;

private:
    QPropertyAnimation *label_choose_animi;
    QPropertyAnimation *label_confirm_animi;
    QPropertyAnimation *label_cancel_animi;
    QPropertyAnimation *animi;

    customFrame *frame_titleBar;
    customLabel *label_choose;

    customDynamicButton *Btn_Confirm;
    customDynamicButton *Btn_Cancel;

    customLabel *Btn_Confirm_label;
    customLabel *Btn_Cancel_label;

    NewPJProjectCellPage *cellPage;

    QFrame *VLine_Splitter;

    customButtonListWidget *BtnListWidget1;
    customButtonListWidget *BtnListWidget2;

    QPoint  m_startPoint;
    QPoint  m_windowPoint;
    bool    m_move;

private:
    void Init();
    void setEventConnections();

private:
    CellUiGlobal::COLOR_SCHEME m_mode;

protected:
#ifdef Q_OS_WIN32
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
#endif

    virtual void mousePressEvent(QMouseEvent *event);

    virtual void mouseMoveEvent(QMouseEvent *event);

    virtual void mouseReleaseEvent(QMouseEvent *event);

signals:
    void enableColorScheme(CellUiGlobal::COLOR_SCHEME mode);

private slots:
    void setColorScheme(CellUiGlobal::COLOR_SCHEME mode);
    void Tab_Cell_clicked();
    void Tab_Others_clicked();
    void Tab_Empty_clicked();
    void Tab_CPP_clicked();
    void Tab_Py_clicked();
    void Btn_Cancel_clicked();
};

#endif // LAUNCHERNEWPJDIALOG_H
