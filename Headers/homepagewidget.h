#ifndef HOMEPAGEWIDGET_H
#define HOMEPAGEWIDGET_H

#include <QWidget>
#include "Kits/_utility.h"

namespace Ui {
class HomePageWidget;
}

class HomePageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HomePageWidget(QWidget *parent = nullptr);
    ~HomePageWidget();

private:
    Ui::HomePageWidget *ui;

private:
    COLOR_SCHEME m_mode;

private:
    void Init();
    void setAllGraphBtnsUnchecked();

private slots:
    void setColorScheme(COLOR_SCHEME mode);
    void on_Btn_grid_clicked();
    void on_Btn_list_clicked();
};

#endif // HOMEPAGEWIDGET_H
