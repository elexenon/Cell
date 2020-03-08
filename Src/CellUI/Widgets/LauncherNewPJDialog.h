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

#include "../../CellCore/Kits/CellUtility.h"    // ColorScheme
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
class NewPJPredictEarPage;
class customButtonListWidget;

class LauncherNewPJDialog : public customWinstyleDialog
{
    Q_OBJECT

public:
    explicit LauncherNewPJDialog(Cell::ColorScheme globalMode,QWidget *parent = nullptr);
    ~LauncherNewPJDialog();

private:
    customTitleBar *titleBar;

    customLabel *label_choose;

    ButtonWithText *btnConfirm;
    ButtonWithText *btnCancel;

    QStackedWidget *stackedWidget;

    NewPJProjectCellPage *cellPage;
    NewPJPredictEarPage  *prePage;

    customButtonListWidget *btnListWidget1;
    customButtonListWidget *btnListWidget2;

    CellProjectEntity *currEntity;

private:
    virtual void
    init() override;

    virtual void
    setEventConnections() override;

    void
    judgeValidProject();

signals:
    void
    projectSettled(CellProjectEntity *entity);

private Q_SLOTS:
    inline void
    btnCancelClicked() { this->close(); }

    void
    btnConfirmClicked();

    void
    btnListWidget1Clicked(int id);

    void
    btnListWidget2Clicked(int id);

    void
    setName(const QString &name);

    void
    setPath(const QString &path);
};

#endif // LAUNCHERNEWPJDIALOG_H
