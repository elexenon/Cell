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
class LauncherNewPJDialog;
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
class customLine;
class QButtonGroup;
class customButtonListWidget;

class Launcher : public customWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
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

    Workshop            *workshop;
    LauncherHomepage    *homePage;
    LauncherSettings    *settingsPage;
    LauncherGuideDialog *guideDialog;
    LauncherNewPJDialog *newPJDialog;

    customFrame         *frame_titleBar;
    customDynamicButton *Btn_NewProject;
    customDynamicButton *Btn_OpenProject;

    customLabel *Btn_NewProject_Icon;
    customLabel *Btn_NewProject_Function;
    customLabel *Btn_NewProject_Hint;

    customLabel *Btn_OpenProject_Icon;
    customLabel *Btn_OpenProject_Function;
    customLabel *Btn_OpenProject_Hint;

    notificationCenter *notificationCenter;
    customButtonListWidget *BtnlistWidget;

    QButtonGroup *tabsGroup;

private:
    QPoint                   m_startPoint;
    QPoint                   m_windowPoint;
    bool                     m_move;
    bool                     isMaxSize = false;
    PAGE_TYPE    currentPage;
    CellUiGlobal::COLOR_SCHEME m_mode;

private:
    void InitLauncher();
    void setEventConnections();
    void startPageSwitchAnimation(PAGE_TYPE nextPage);

protected:
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);

    virtual void mousePressEvent(QMouseEvent *event);

    virtual void mouseMoveEvent(QMouseEvent *event);

    virtual void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void setColorScheme(CellUiGlobal::COLOR_SCHEME mode);
    void on_Btn_mini_clicked();
    void on_Btn_close_clicked();
    void Tab_HomePage_clicked();
    void Tab_Settings_clicked();
    void Tab_Guide_clicked();
    void Btn_NewProject_clicked();
    void on_Btn_max_clicked();
};
#endif
