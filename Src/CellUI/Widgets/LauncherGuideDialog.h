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

class customFrame;
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
    QVBoxLayout         *mainLayout;
    customFrame         *titleBar;
    QLabel              *icon;
    customLabel         *labelTitle;
    customStackedWidget *mainStackedWidget;
    customFrame         *bottomBar;
    QCheckBox           *checkBox;
    ButtonWithText      *btnClose;
    ButtonWithText      *btnNewPJ;

private:
    void init();
    virtual void setEventConnections() override;

signals:
    void clickedNewPJ();

private slots:
    virtual void setColorScheme(CellUiGlobal::COLOR_SCHEME) override;
    inline
    void         btnCloseClicked() { this->close(); }
    inline
    void         btnNewPJClicked() { emit clickedNewPJ(); this->close(); }
};

#endif // LauncherGuideDialog_H
