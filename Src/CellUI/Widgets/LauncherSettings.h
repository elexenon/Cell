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
class QVBoxLayout;
class customMaskDialog;
class Launcher;
class customSwitch;
class QJsonObject;

class LauncherSettings : public customFrame
{
    Q_OBJECT
    enum SaveAttribute{
        Auto,
        MultiInstance
    };
    static const QString path;
public:
    explicit LauncherSettings(QWidget *parent = nullptr);
    ~LauncherSettings();

    void LauncherSetColorSchemeModeCall(Cell::ColorScheme mode);
    inline
    void getLauncherPtr(Launcher *ptr) { launcherPtr = ptr; }

private:
    void init();
    void initsettingsObj();
    void write(SaveAttribute key, const QString &value);
    void loadFile();
    void saveFile();
    void read(const QJsonObject&);
    void setColorScheme(Cell::ColorScheme mode);
    void setEventConnections();

    QVBoxLayout *mainLayout;

    // OptionBlock blockGeneral Combination;
    customOptionBlock     *blockGeneral;
    // Item Appear Combination.
    customOptionBlockItem *blockGeneralItemAppear;
    customDialogButton    *dBtnAppear;
    // Item Auto Combination.
    customOptionBlockItem *blockGeneralItemAuto;
    customSwitch          *switchAuto;
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

signals:
    void enableColorScheme(Cell::ColorScheme mode);

private Q_SLOTS:
    void btnColorSchemeClicked();
    void btnLanguageClicked();
    void switchAutoClicked(bool checked);
    void switchMultiClicked(bool checked);
    void btnBrightClicked();
    void btnDarkClicked();
};

#endif // LauncherSettings_H
