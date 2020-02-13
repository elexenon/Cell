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
#include "../../CellCore/CellProjectEntity.h"

class customTitleBar;
class customLabel;
class QPropertyAnimation;
class QGraphicsDropShadowEffect;
class ButtonWithText;
class QStackedWidget;
class QFrame;
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
    customTitleBar *titleBar;

    customLabel *label_choose;

    ButtonWithText *btnConfirm;
    ButtonWithText *btnCancel;

    NewPJProjectCellPage *cellPage;

    QFrame *VLineSplitter;

    customButtonListWidget *btnListWidget1;
    customButtonListWidget *btnListWidget2;

    CellProjectEntity *currEntity;

private:
    void Init();
    void judgeValidProject();
    virtual void setEventConnections() override;

signals:
    void enableColorScheme(CellUiGlobal::COLOR_SCHEME mode);
    void projectSettled(CellProjectEntity *entity);

private slots:
    inline
    void btnCancelClicked() { this->close(); }
    void btnConfirmClicked();
    void btnListWidget1Clicked(int id);
    void btnListWidget2Clicked(int id);
    void setName(const QString &name);
    void setPath(const QString &path);
    virtual void setColorScheme(CellUiGlobal::COLOR_SCHEME) override;
};

#endif // LAUNCHERNEWPJDIALOG_H
