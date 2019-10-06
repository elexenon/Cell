#ifndef SETTINGSPAGEWIDGET_H
#define SETTINGSPAGEWIDGET_H

#include <QWidget>
#include "_utility.h"

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

private:
    Ui::SettingsPageWidget *ui;

private:
    void Init();
};

#endif // SETTINGSPAGEWIDGET_H
