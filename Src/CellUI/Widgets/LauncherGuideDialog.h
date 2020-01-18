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
#include "../CustomBaseWidgets/customWinstyleDialog.h"

class QPropertyAnimation;
class customTitleBar;
class customFrame;

namespace Ui {
class LauncherGuideDialog;
}

class LauncherGuideDialog : public customWinstyleDialog
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
    void Init();

private slots:
    virtual void setColorScheme(CellUiGlobal::COLOR_SCHEME) override;
    void    on_Btn_close_clicked();
    void    on_pushButton_clicked();
};

#endif // LauncherGuideDialog_H
