// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#ifndef LAUNCHERNEWPJGUI_H
#define LAUNCHERNEWPJGUI_H

#include "../CustomBaseWidgets/customWinstyleDialog.h"

class QVBoxLayout;
class QStackedWidget;
class customFrame;
class ButtonWithText;
class customTitleBar;
class NewPJGUIModel;
class newPJPageBase;

class LauncherNewPJGUI : public customWinstyleDialog
{
    Q_OBJECT
public:
    explicit LauncherNewPJGUI(QWidget *parent = nullptr);
    ~LauncherNewPJGUI() = default;

private:
    virtual void
    init() override;

    virtual void
    setEventConnections() override;

    QVBoxLayout    *mainLayout;
    customTitleBar *titleBar;
    QStackedWidget *stackedWidget;
    NewPJGUIModel  *modelPage;
    newPJPageBase  *configPage;
    customFrame    *bottomBar;
    ButtonWithText *btnCancel;
    ButtonWithText *btnBackward;
    ButtonWithText *btnForward;

Q_SIGNALS:
    void
    projectSettled();

private Q_SLOTS:

    void
    setName(const QString &name);

    void
    setPath(const QString &path);
};

#endif // LAUNCHERNEWPJGUI_H
