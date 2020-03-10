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

    void setCheckBox(bool checked);

private:
    virtual void
    init() override;

    virtual void
    setEventConnections() override;

    QVBoxLayout         *mainLayout;
    customTitleBar      *titleBar;
    customStackedWidget *mainStackedWidget;
    customFrame         *bottomBar;
    QCheckBox           *checkBox;
    ButtonWithText      *btnClose;
    ButtonWithText      *btnNewPJ;
    bool                 onCloseNewPJ;

protected:
    virtual void
    showEvent(QShowEvent *e) override;

    virtual void
    closeEvent(QCloseEvent *e) override;

Q_SIGNALS:
    void
    clickedNewPJ();

    void
    checkBoxClicked(bool checked);

private Q_SLOTS:
    void
    fade();
};

#endif // LauncherGuideDialog_H
