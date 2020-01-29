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
class customComboBox;
class customButton;

class LauncherSettings : public customFrame
{
    Q_OBJECT
    static const QString QSS_OPTIONBLOCK;
public:
    explicit LauncherSettings(QWidget *parent = nullptr);
    ~LauncherSettings() = default;

    void LauncherSetColorSchemeModeCall(CellUiGlobal::COLOR_SCHEME mode);

private slots:
    void Btn_bright_clicked();
    void Btn_dark_clicked();

private:
    QPropertyAnimation *label_general_animi;
    QPropertyAnimation *label_auto_hint_animi;
    QPropertyAnimation *optionBlock1_animi;
    QPropertyAnimation *optionBlock2_animi;

    // OptionBlock blockGeneral Combination;
    customOptionBlock       *blockGeneral;
    customOptionBlockItem   *blockGeneral_ItemAppear;
    customOptionBlockItem   *blockGeneral_ItemAuto;

    // This is a combination of customOptionBlockSector.

    // ComboBox Appear Combination.
    customComboBox          *cBoxAppear;
    customOptionBlockItem   *cBoxAppear_ItemFusion;
    customButton            *cBoxAppear_BtnFusion;
    customOptionBlockItem   *cBoxAppear_ItemDark;
    customButton            *cBoxAppear_BtnDark;




private:
    void   Init();
    void   setColorScheme(CellUiGlobal::COLOR_SCHEME mode);
    void   setEventConnections();

signals:
    void enableColorScheme(CellUiGlobal::COLOR_SCHEME mode);
};

#endif // LauncherSettings_H
