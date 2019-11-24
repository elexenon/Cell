// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
//
// This is part of main launcher's stackwidget.
#ifndef SETTINGSPAGEWIDGET_H
#define SETTINGSPAGEWIDGET_H

#include "Kits/customFrame.h"
#include "Kits/cell_util.h" // COLOR_SCHEME

namespace Ui {
class SettingsPageWidget;
}
class customWidget;
class QScrollArea;
class QPropertyAnimation;
class customFrame;
class customLabel;
class QFrame;
class QGraphicsDropShadowEffect;
class QPushButton;
class QCheckBox;
class QGraphicsDropShadowEffect;

class SettingsPageWidget : public customFrame
{
    Q_OBJECT
public:
    explicit SettingsPageWidget(QWidget *parent = nullptr);
    ~SettingsPageWidget() = default;

    void mainWindowSetColorSchemeModeCall(CellGlobal::COLOR_SCHEME mode);

private slots:
    void Btn_bright_clicked();
    void Btn_dark_clicked();

private:
    QPropertyAnimation     *line_color_animi;
    QPropertyAnimation     *label_appearence_animi;
    QPropertyAnimation     *label_general_animi;
    QPropertyAnimation     *label_auto_hint_animi;
    QPropertyAnimation     *optionBlock1_animi;
    QPropertyAnimation     *optionBlock2_animi;
    QPropertyAnimation     *animi;

    QGraphicsDropShadowEffect *Btn_dark_dse;
    QGraphicsDropShadowEffect *Btn_bright_dse;

    customFrame            *optionBlock1;
    customFrame            *optionBlock2;

    QPushButton            *Btn_dark;
    QPushButton            *Btn_bright;

    customLabel            *label_appearence;
    customLabel            *label_general;
    customLabel            *label_auto_hint;

    QFrame                 *line_color;

private:
    CellGlobal::COLOR_SCHEME m_mode;

private:
    void   Init();
    void   modulesChangeToDarkness();
    void   modulesChangeToBrightness();
    void   setEventConnections();

signals:
    void enableColorScheme(CellGlobal::COLOR_SCHEME mode);
};

#endif // SETTINGSPAGEWIDGET_H
