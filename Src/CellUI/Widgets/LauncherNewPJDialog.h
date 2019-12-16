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

namespace Ui {
class LauncherNewPJDialog;
}

class LauncherNewPJDialog : public customDialog
{
    Q_OBJECT

public:
    explicit LauncherNewPJDialog(CellGlobal::COLOR_SCHEME globalMode,QWidget *parent = nullptr);
    ~LauncherNewPJDialog();

private:
    Ui::LauncherNewPJDialog *ui;

private:
    QPropertyAnimation *label_choose_animi;
    QPropertyAnimation *label_cell_animi;
    QPropertyAnimation *label_others_animi;
    QPropertyAnimation *label_empty_animi;
    QPropertyAnimation *label_cpp_animi;
    QPropertyAnimation *label_py_animi;
    QPropertyAnimation *label_confirm_animi;
    QPropertyAnimation *label_cancel_animi;
    QPropertyAnimation *animi;

    QGraphicsDropShadowEffect *eff_dse;

    customStaticButton *Tab_Cell;
    customStaticButton *Tab_Others;
    customStaticButton *Tab_Empty;
    customStaticButton *Tab_CPP;
    customStaticButton *Tab_Py;

    customFrame *frame_titleBar;
    customLabel *label_choose;
    customLabel *label_project;
    customLabel *label_file;
    customLabel *Tab_Cell_Label;
    customLabel *Tab_Others_Label;
    customLabel *Tab_Empty_Label;
    customLabel *Tab_CPP_Label;
    customLabel *Tab_Py_Label;

    QFrame *LauncherNewPJ_line_splitter1;
    QFrame *LauncherNewPJ_line_splitter2;

    customDynamicButton *Btn_Confirm;
    customDynamicButton *Btn_Cancel;

    customLabel *Btn_Confirm_label;
    customLabel *Btn_Cancel_label;

    NewPJProjectCellPage *cellPage;

    QList<customStaticButton*> *tabs;

    QPoint  m_startPoint;
    QPoint  m_windowPoint;
    bool    m_move;

private:
    void Init();
    void setAllTabsUnchecked();
    void setEventConnections();

private:
    CellGlobal::COLOR_SCHEME m_mode;

protected:
#ifdef Q_OS_WIN32
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
#endif

    virtual void mousePressEvent(QMouseEvent *event);

    virtual void mouseMoveEvent(QMouseEvent *event);

    virtual void mouseReleaseEvent(QMouseEvent *event);

signals:
    void enableColorScheme(CellGlobal::COLOR_SCHEME mode);

private slots:
    void setColorScheme(CellGlobal::COLOR_SCHEME mode);
    void Tab_Cell_clicked();
    void Tab_Others_clicked();
    void Tab_Empty_clicked();
    void Tab_CPP_clicked();
    void Tab_Py_clicked();
    void Btn_Cancel_clicked();
};

#endif // LAUNCHERNEWPJDIALOG_H
