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
