#ifndef SETTINGSPAGEWIDGET_H
#define SETTINGSPAGEWIDGET_H

#include <QWidget>
#include "Kits/_utility.h"

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
    QList<QFrame*>         *optionBlocks;

private:
    void   Init();
    void   modulesChangeToDarkness();
    void   modulesChangeToBrightness();

signals:
    // Custom signals.
    void enableColorScheme(COLOR_SCHEME mode);
};

#endif // SETTINGSPAGEWIDGET_H
