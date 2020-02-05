// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef Launcher_H
#define Launcher_H

#include "../CustomBaseWidgets/customWinstyleWidget.h"
#include "../../CellCore/Kits/CellUtility.h"   // COLOR_SCHEME & FADE_TYPE

QT_BEGIN_NAMESPACE
namespace Ui { class Launcher; }
QT_END_NAMESPACE

class LauncherGuideDialog;
class LauncherNewPJDialog;
class LauncherHomepage;
class Workshop;
class LauncherSettings;

class QGraphicsOpacityEffect;
class QPropertyAnimation;
class customTitleBar;
class notificationCenter;
class customButtonListWidget;
class CellDevelopTestStation;

class ButtonWithIconTextHint;

class Launcher : public customWinstyleWidget
{
    Q_OBJECT
public:
    explicit Launcher(QWidget *parent = nullptr);
    ~Launcher();
    enum PAGE_TYPE{
        _HOME,
        _SETTINGS
    };
private:
    Ui::Launcher           *ui;

    QGraphicsOpacityEffect    *opacityEffect;
    QGraphicsDropShadowEffect *eff_dse;

    QPropertyAnimation *this_animi;
    QPropertyAnimation *frame_titleBar_animi;
    QPropertyAnimation *Btn_NewProject_Function_animi;
    QPropertyAnimation *Btn_NewProject_Hint_animi;
    QPropertyAnimation *Btn_OpenProject_Function_animi;
    QPropertyAnimation *Btn_OpenProject_Hint_animi;
    QPropertyAnimation *line_animi;

    Workshop            *workshop = nullptr;
    LauncherHomepage    *homePage;
    LauncherSettings    *settingsPage;
    LauncherGuideDialog *guideDialog;
    LauncherNewPJDialog *newPJDialog = nullptr;

    customTitleBar      *titleBar;

    ButtonWithIconTextHint *Btn_NewProject;
    ButtonWithIconTextHint *Btn_OpenProject;

    notificationCenter *notificationCenter;
    customButtonListWidget *BtnlistWidget;

    CellDevelopTestStation *testForm;

private:
    bool                       isMaxSize = false;
    PAGE_TYPE                  currentPage;

private:
    void InitLauncher();
    void setEventConnections();
    void startPageSwitchAnimation(PAGE_TYPE nextPage);

protected:


private slots:
    void on_Btn_mini_clicked();
    void on_Btn_close_clicked();
    void Tab_HomePage_clicked();
    void Tab_Settings_clicked();
    void Tab_Guide_clicked();
    void Tab_Test_clicked();
    void Btn_NewProject_clicked();
    void on_Btn_max_clicked();
};
#endif
