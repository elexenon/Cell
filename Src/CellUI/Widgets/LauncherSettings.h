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
#include "../../CellCore/Kits/CellUtility.h" // COLOR_SCHEME

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

class LauncherSettings : public customFrame
{
    Q_OBJECT
public:
    explicit LauncherSettings(QWidget *parent = nullptr);
    ~LauncherSettings() = default;

    void LauncherSetColorSchemeModeCall(CellUiGlobal::COLOR_SCHEME mode);
    inline
    void getLauncherPtr(QWidget *ptr) { launcherPtr = ptr; }

private:
    void   init();
    void   setColorScheme(CellUiGlobal::COLOR_SCHEME mode);
    void   setEventConnections();

    QVBoxLayout *mainLayout;

    // OptionBlock blockGeneral Combination;
    customOptionBlock     *blockGeneral;
    customOptionBlockItem *blockGeneral_ItemAppear;
    // ComboBox Appear Combination.
    customDialogButton    *cBoxAppear;
    customDialogButton    *cBoxAuto;
    customOptionBlockItem *blockGeneral_ItemAuto;

    QWidget *launcherPtr;

signals:
    void enableColorScheme(CellUiGlobal::COLOR_SCHEME mode);

private Q_SLOTS:
    void btnColorSchemeClicked();
    void btnAutoSwitchClicked();
    void Btn_bright_clicked();
    void Btn_dark_clicked();
};

#endif // LauncherSettings_H
