// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#ifndef LAUNCHERNEWPJGUI_H
#define LAUNCHERNEWPJGUI_H

#include "../CustomBaseWidgets/customWinstyleDialog.h"

class QVBoxLayout;
class customLabel;
class customFrame;
class customNavigator;
class ButtonWithText;
class customTitleBar;
class customSmoothScrollArea;

class LauncherNewPJGUI : public customWinstyleDialog
{
public:
    explicit LauncherNewPJGUI(QWidget *parent = nullptr);
    ~LauncherNewPJGUI() = default;

private:
    virtual void
    init() override;

    virtual void
    setEventConnections() override;

    QVBoxLayout            *mainLayout;
    customTitleBar         *titleBar;
    customNavigator        *navigator;
    customSmoothScrollArea *scrollArea;
    customFrame            *bottomBar;
    ButtonWithText         *btnCancel;
    ButtonWithText         *btnBackward;
    ButtonWithText         *btnForward;
};

#endif // LAUNCHERNEWPJGUI_H
