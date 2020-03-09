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
#include "../../CellCore/Kits/CellUtility.h" // ColorScheme & FadeAnimiType
#include "../../CellCore/CellProjectEntity.h"

class LauncherGuideDialog;
class LauncherNewPJDialog;
class LauncherHomepage;
class Workshop;
class LauncherSettings;

class QGraphicsOpacityEffect;
class customTitleBar;
class notificationCenter;
class customButtonListWidget;
class CellDevelopTestStation;
class ButtonWithIcon;
class ButtonWithIconTextHint;
class QStackedWidget;

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

    const QRect
    maskGeometry();

private:
    void
    startPageSwitchAnimation(PAGE_TYPE nextPage);

    void
    _launcherWorkshop();
    //! Inhrits From
    //! CellWidgetGlobalInterface.
    virtual void
    init() override;

    virtual void
    setEventConnections() override;

    QGraphicsOpacityEffect *opacityEffect;

    Workshop            *workshop = nullptr;
    LauncherHomepage    *homePage = nullptr;
    LauncherSettings    *settingsPage = nullptr;
    LauncherGuideDialog *guideDialog = nullptr;
    LauncherNewPJDialog *newPJDialog = nullptr;

    customTitleBar *titleBar;
    ButtonWithIcon *btnMini;
    ButtonWithIcon *btnMax;
    ButtonWithIcon *btnClose;

    QStackedWidget *stackedWidget;

    ButtonWithIconTextHint *btnNewPJ;
    ButtonWithIconTextHint *btnOpenPJ;

    notificationCenter *notificationCenter;

    customButtonListWidget *btnListWidget;

    CellDevelopTestStation *testForm;

    bool      isMaxSize = false;
    bool      onShowGuide = true;
    PAGE_TYPE currentPage;

private Q_SLOTS:
    void
    btnMiniClicked();

    void
    btnMaxClicked();

    void
    btnCloseClicked();

    void
    tabHomeClicked();

    void
    tabSettingsClicked();

    void
    tabGuideClicked();

    void
    tabTestClicked();

    void
    btnNewClicked();

    void
    btnOpenClicked();

    void
    launchWorkShop(CellProjectEntity *entity);

    void
    launchWorkShopByPath(const QString &path);
};
#endif
