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
class QScrollArea;
class QPropertyAnimation;
class customFrame;
class customLabel;
class QFrame;
class QGraphicsDropShadowEffect;
class QPushButton;
class QCheckBox;
class QGraphicsDropShadowEffect;
class QComboBox;

class LauncherSettings : public customFrame
{
    Q_OBJECT
    static const QString QSS_OPTIONBLOCK;
public:
    explicit LauncherSettings(QWidget *parent = nullptr);
    ~LauncherSettings() = default;

    void LauncherSetColorSchemeModeCall(CellGlobal::COLOR_SCHEME mode);

private slots:
    void Btn_bright_clicked();
    void Btn_dark_clicked();

private:
    QPropertyAnimation *label_general_animi;
    QPropertyAnimation *label_auto_hint_animi;
    QPropertyAnimation *optionBlock1_animi;
    QPropertyAnimation *optionBlock2_animi;
    QPropertyAnimation *animi;

    QGraphicsDropShadowEffect *Btn_dark_dse;
    QGraphicsDropShadowEffect *Btn_bright_dse;

    customFrame *optionBlock1;
    customFrame *optionBlock2;

    customLabel *label_general;
    customLabel *label_auto_hint;
    customLabel *label_colorScheme;
    customLabel *label_auto;

    QComboBox *comboBox_ColorScheme;
    QComboBox *comboBox_Auto;

    QFrame *LauncherSettings_line_splitter1;

private:
    CellGlobal::COLOR_SCHEME m_mode;

private:
    void   Init();
    void   setColorScheme(CellGlobal::COLOR_SCHEME mode);
    void   setEventConnections();

signals:
    void enableColorScheme(CellGlobal::COLOR_SCHEME mode);
};

#endif // LauncherSettings_H
