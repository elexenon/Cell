// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
//
// This is part of main launcher's stackwidget.
#ifndef LauncherSettings_H
#define LauncherSettings_H

#include "../CustomBaseWidgets/customFrame.h"
#include "../../CellCore/CellSettings.h"
#include "../../CellCore/Kits/CellUtility.h" // ColorScheme

namespace Ui {
class LauncherSettings;
}
class QPropertyAnimation;
class QGraphicsDropShadowEffect;
class customOptionBlock;
class customOptionBlockItem;
class customDialogButton;
class customButton;
class customNavigator;
class QVBoxLayout;
class QHBoxLayout;
class customMaskDialog;
class Launcher;
class customSwitch;
class QJsonObject;

class LauncherSettings : public customFrame, implements CellSettings
{
    Q_OBJECT
    static const QString path;
public:
    explicit LauncherSettings(QWidget *parent = nullptr);
    ~LauncherSettings();

    void
    LauncherSetColorSchemeModeCall(Cell::ColorScheme mode);

    inline void
    getLauncherPtr(Launcher *ptr) { launcherPtr = ptr; }

    inline bool
    showGuideDialog() { return settingsObj["CellLauncherSettgins"].toObject()["OnShowGuideDialog"] == CMPSTR("true"); }

private:
    virtual void
    init() override;

    virtual void
    setEventConnections() override;

    void
    initsettingsObj();

    virtual void
    write(SaveAttribute key, const QString &value) override;

    virtual void
    loadFile() override;

    virtual void
    saveFile() override;

    virtual void
    read(const QJsonObject&) override;

    QHBoxLayout *mainLayout;
    QVBoxLayout *VLayoutRight;

    customNavigator *navigator;
    // OptionBlock blockGeneral Combination;
    customOptionBlock     *blockGeneral;
    // Item Appear Combination.
    customOptionBlockItem *blockGeneralItemAppear;
    customDialogButton    *dBtnAppear;
    // Item Auto Combination.
    customOptionBlockItem *blockGeneralItemAuto;
    customSwitch          *switchAuto;
    // Item Abate Combination
    customOptionBlockItem *blockGeneralItemAbate;
    customSwitch          *switchAbate;
    // Item Language Combination.
    customOptionBlockItem *blockGeneralItemLan;
    customDialogButton    *dBtnLan;

    // OptionBlock blockWorkshop Combination.
    customOptionBlock     *blockWorkshop;
    // Item Multi Combination.
    customOptionBlockItem *blockWorkshopItemMulti;
    customSwitch          *switchMulti;

    Launcher *launcherPtr;

    QJsonObject settingsObj;

Q_SIGNALS:
    void
    enableColorScheme(Cell::ColorScheme mode);

public Q_SLOTS:
    inline void
    setOnShowGuide(bool checked) { write(onShowGuideDialog, checked ? "true" : "false"); }

private Q_SLOTS:
    void
    btnColorSchemeClicked();

    void
    btnLanguageClicked();

    void
    btnBrightClicked();

    void
    btnDarkClicked();
};

#endif // LauncherSettings_H
