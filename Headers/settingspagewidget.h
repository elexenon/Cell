#ifndef SETTINGSPAGEWIDGET_H
#define SETTINGSPAGEWIDGET_H

#include <QWidget>
#include "Kits/_utility.h"
#include "Kits/customFrame.h"

namespace Ui {
class SettingsPageWidget;
}

class SettingsPageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsPageWidget(QWidget *parent = nullptr);
    ~SettingsPageWidget();

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

    customFrame            *frame_optionBlock2;
    customFrame            *frame_optionBlock3;
    customFrame            *frame_optionBlock1;

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
