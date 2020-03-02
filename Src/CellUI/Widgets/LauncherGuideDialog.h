// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef LauncherGuideDialog_H
#define LauncherGuideDialog_H

#include "../../CellCore/Kits/CellUtility.h"    // ColorScheme
#include "../CustomBaseWidgets/customWinstyleDialog.h"

class customFrame;
class customTitleBar;
class customLabel;
class customStackedWidget;
class QVBoxLayout;
class QLabel;
class QCheckBox;
class QStackedWidget;
class ButtonWithText;
class ButtonWithIcon;

class LauncherGuideDialog : public customWinstyleDialog
{
    Q_OBJECT
public:
    explicit LauncherGuideDialog(QWidget *parent = nullptr);
    ~LauncherGuideDialog() = default;

private:
    void init();
    virtual void setEventConnections() override;

    QVBoxLayout         *mainLayout;
    customTitleBar      *titleBar;
    customStackedWidget *mainStackedWidget;
    customFrame         *bottomBar;
    QCheckBox           *checkBox;
    ButtonWithText      *btnClose;
    ButtonWithText      *btnNewPJ;

protected:
    virtual void showEvent(QShowEvent *e) override;

signals:
    void clickedNewPJ();

public Q_SLOTS:
    virtual void setColorScheme(Cell::ColorScheme) override;

private Q_SLOTS:
    void         fade();
    inline
    void         btnNewPJClicked() { emit clickedNewPJ(); close(); }
};

#endif // LauncherGuideDialog_H
