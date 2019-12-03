// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef Launcher_H
#define Launcher_H

#include "../CustomBaseWidgets/customWidget.h"
#include "../../CellCore/Kits/CellUtility.h"   // PAGE_TYPE & COLOR_SCHEME & FADE_TYPE

QT_BEGIN_NAMESPACE
namespace Ui { class Launcher; }
QT_END_NAMESPACE

class LauncherGuideDialog;
class LauncherHomepage;
class Workshop;
class LauncherSettings;
class QPushButton;
class QGraphicsOpacityEffect;
class QPropertyAnimation;
class customFrame;
class customStaticButton;
class customDynamicButton;
class customLabel;
class notificationCenter;
class QLabel;

class Launcher : public customWidget
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

    QGraphicsOpacityEffect *opacityEffect;
    QGraphicsDropShadowEffect *eff_dse;

    QPropertyAnimation     *this_animi;
    QPropertyAnimation     *frame_titleBar_animi;
    QPropertyAnimation     *Btn_NewProject_Function_animi;
    QPropertyAnimation     *Btn_NewProject_Hint_animi;
    QPropertyAnimation     *Btn_OpenProject_Function_animi;
    QPropertyAnimation     *Btn_OpenProject_Hint_animi;
    QPropertyAnimation     *Label_HomePage_animi;
    QPropertyAnimation     *Label_Settings_animi;
    QPropertyAnimation     *Label_Guide_animi;

    Workshop               *workshop;
    LauncherHomepage       *homePage;
    LauncherSettings     *settingsPage;
    LauncherGuideDialog    *guideDialog;

    customFrame            *frame_titleBar;
    customStaticButton     *Tab_HomePage;
    customStaticButton     *Tab_Settings;
    customStaticButton     *Tab_Guide;
    customDynamicButton    *Btn_NewProject;
    customDynamicButton    *Btn_OpenProject;

    customLabel            *Tab_HomePage_Label;
    customLabel            *Tab_Settings_Label;
    customLabel            *Tab_Guide_Label;

    customLabel            *Btn_NewProject_Icon;
    customLabel            *Btn_NewProject_Function;
    customLabel            *Btn_NewProject_Hint;

    customLabel            *Btn_OpenProject_Icon;
    customLabel            *Btn_OpenProject_Function;
    customLabel            *Btn_OpenProject_Hint;

    notificationCenter     *notificationCenter;
    QPushButton            *Noticenter_Btn_popUp;

private:
    QPoint                   m_startPoint;
    QPoint                   m_windowPoint;
    bool                     m_move;
    PAGE_TYPE    currentPage;
    CellGlobal::COLOR_SCHEME m_mode;

private:
    void InitLauncher();
    void setEventConnections();
    void startPageSwitchAnimation(PAGE_TYPE nextPage);

protected:
#ifdef Q_OS_WIN32
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
#endif

    virtual void mousePressEvent(QMouseEvent *event);

    virtual void mouseMoveEvent(QMouseEvent *event);

    virtual void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void setColorScheme(CellGlobal::COLOR_SCHEME mode);
    void on_Btn_mini_clicked();
    void on_Btn_close_clicked();
    void Tab_HomePage_clicked();
    void Tab_Settings_clicked();
    void Tab_Guide_clicked();
    void Btn_NewProject_clicked();
};
#endif
