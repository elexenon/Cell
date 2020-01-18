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
#include "../CustomBaseWidgets/customWinstyleDialog.h"

class customTitleBar;
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

class LauncherNewPJDialog : public customWinstyleDialog
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

    customTitleBar *titleBar;

    customLabel *label_choose;

    customDynamicButton *Btn_Confirm;
    customDynamicButton *Btn_Cancel;

    customLabel *Btn_Confirm_label;
    customLabel *Btn_Cancel_label;

    NewPJProjectCellPage *cellPage;

    QFrame *VLine_Splitter;

    customButtonListWidget *BtnListWidget1;
    customButtonListWidget *BtnListWidget2;

private:
    void Init();
    void setEventConnections();

signals:
    void enableColorScheme(CellUiGlobal::COLOR_SCHEME mode);

private slots:
    virtual void setColorScheme(CellUiGlobal::COLOR_SCHEME) override;
    void Tab_Cell_clicked();
    void Tab_Others_clicked();
    void Tab_Empty_clicked();
    void Tab_CPP_clicked();
    void Tab_Py_clicked();
    void Btn_Cancel_clicked();
};

#endif // LAUNCHERNEWPJDIALOG_H
