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
class customLabel;
class QFrame;
class QGraphicsDropShadowEffect;
class QPushButton;
class QCheckBox;
class QGraphicsDropShadowEffect;
class QComboBox;
class customOptionBlock;
class customOptionBlockSector;
class customOptionBlockItem;


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

    customOptionBlockItem *itemAppear;
    customOptionBlockItem *itemAuto;
    customOptionBlockSector *sector1;

    customOptionBlockItem *itemPath;
    customOptionBlockItem *itemKit;
    customOptionBlockSector *sector2;

    customOptionBlock *blockGeneral;

    QComboBox *comboBox1;
    QComboBox *comboBox2;
    QComboBox *comboBox3;
    QComboBox *comboBox4;

private:
    void   Init();
    void   setColorScheme(CellUiGlobal::COLOR_SCHEME mode);
    void   setEventConnections();

signals:
    void enableColorScheme(CellUiGlobal::COLOR_SCHEME mode);
};

#endif // LauncherSettings_H
