// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Kits/customWidget.h" //Also includes "Kits/cell_util.h" : PAGE_TYPE & COLOR_SCHEME & FADE_TYPE

QT_BEGIN_NAMESPACE
namespace Ui { class mainWindow; }
QT_END_NAMESPACE

class GuideDialog;
class HomePageWidget;
class Workshop;
class SettingsPageWidget;
class QPushButton;
class QGraphicsOpacityEffect;
class QPropertyAnimation;
class customFrame;
class customStaticButton;
class customDynamicButton;
class customLabel;
class QLabel;
class notificationCenter;

class mainWindow : public customWidget
{
    Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = nullptr);
    ~mainWindow();

private:
    Ui::mainWindow         *ui;

    QGraphicsOpacityEffect *opacityEffect;

    QPropertyAnimation     *propertyAnimi;
    QPropertyAnimation     *Btn_NewProject_Function_animi;
    QPropertyAnimation     *Btn_NewProject_Hint_animi;
    QPropertyAnimation     *notifiCenter_animi;

    QGraphicsDropShadowEffect *eff_dse;
    QGraphicsDropShadowEffect *eff_dse2;

    Workshop               *workshop;
    HomePageWidget         *homePage;
    SettingsPageWidget     *settingsPage;
    GuideDialog            *guideDialog;

    customFrame            *frame_titleBar;
    customStaticButton     *Tab_HomePage;
    customStaticButton     *Tab_Settings;
    customStaticButton     *Tab_Guide;
    customDynamicButton    *Btn_NewProject;
    customDynamicButton    *Btn_OpenProject;

    QLabel                 *Btn_NewProject_Icon;
    QLabel                 *Btn_NewProject_Function;
    QLabel                 *Btn_NewProject_Hint;

    QLabel                 *Btn_OpenProject_Icon;
    QLabel                 *Btn_OpenProject_Function;
    QLabel                 *Btn_OpenProject_Hint;

    notificationCenter     *notificationCenter;
    QPushButton            *Btn_popUp;

private:
    QPoint       m_startPoint;
    QPoint       m_windowPoint;
    bool         m_move;
    bool         popUpNotificationCenterAuto;
    PAGE_TYPE    currentPage;
    COLOR_SCHEME m_mode;

private:
    void InitMainWindow();  
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
    void setColorScheme(COLOR_SCHEME mode);
    void on_Btn_mini_clicked();
    void on_Btn_close_clicked();
    void Tab_HomePage_clicked();
    void Tab_Settings_clicked();
    void Tab_Guide_clicked();
    void Btn_NewProject_clicked();
    void popUpNotificationCenter();
    void Btn_popUp_clicked();
};
#endif
