// Copyright 2019 CellTek.
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

#include <QWidget>
#include "Kits/cell_util.h" // COLOR_SCHEME

namespace Ui {
class SettingsPageWidget;
}

class customWidget;
class QScrollArea;
class QPropertyAnimation;
class customFrame;
class customLabel;

class SettingsPageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsPageWidget(QWidget *parent = nullptr);
    ~SettingsPageWidget();

    void mainWindowSetColorSchemeModeCall(COLOR_SCHEME mode);

private slots:
    void on_Btn_bright_clicked();

    void on_Btn_dark_clicked();

    void on_radioBtn_bright_clicked();

    void on_radioBtn_dark_clicked();

private:
    Ui::SettingsPageWidget *ui;
    QPropertyAnimation     *frame_optionBlock1_animi;
    QPropertyAnimation     *frame_optionBlock2_animi;
    QPropertyAnimation     *frame_optionBlock3_animi;
    QPropertyAnimation     *frame_optionBlock4_animi;
    QPropertyAnimation     *scrollAreaContents_animi;

    QPropertyAnimation     *label_appearence_animi;
    QPropertyAnimation     *label_automation_animi;
    QPropertyAnimation     *label_auto_hint_animi;
    QPropertyAnimation     *label_license_animi;
    QPropertyAnimation     *label_lice_hint_animi;
    QPropertyAnimation     *label_about_animi;

    QScrollArea            *main_ScrollArea;
    customWidget           *scrollAreaWidgetContents;

    customFrame            *frame_optionBlock2;
    customFrame            *frame_optionBlock3;
    customFrame            *frame_optionBlock1;
    customFrame            *frame_optionBlock4;

    customLabel            *label_appearence;
    customLabel            *label_automation;
    customLabel            *label_auto_hint;
    customLabel            *label_license;
    customLabel            *label_lice_hint;
    customLabel            *label_about;

private:
    COLOR_SCHEME m_mode;

private:
    void   Init();
    void   modulesChangeToDarkness();
    void   modulesChangeToBrightness();

signals:
    // Custom signals.
    void enableColorScheme(COLOR_SCHEME mode);
};

#endif // SETTINGSPAGEWIDGET_H
