#pragma once

#include "Kits/_utility.h"
#include "Kits/qstylesheetloader.h"
#ifdef Q_OS_WIN32
#include "Kits/DropShadowWidget.h"
#endif

#include "guidedialog.h"
#include "homepagewidget.h"
#include "settingspagewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class mainWindow; }
QT_END_NAMESPACE



class mainWindow : public DropShadowWidget
{
    Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = nullptr);
    ~mainWindow();

// Pointers.
private:
    Ui::mainWindow         *ui;
    GuideDialog            *guideDialog;
    QList<QPushButton*>    *mainWindowTabBtns;
    QGraphicsOpacityEffect *opacityEffect;
    QPropertyAnimation     *propertyAnimi;

    HomePageWidget      *homePage;
    SettingsPageWidget  *settingsPage;

// Regular members;
private:
    QPoint m_startPoint;
    QPoint m_windowPoint;
    bool   m_move;
    PAGE_TYPE currentPage;

private:
    void InitMainWindow();
    void setAllTabsUnchecked();
    void startPageSwitchAnimation(PAGE_TYPE nextPage);
    void startFadeInOrOutAnimation(QWidget *target, QWidget *parent, int duration, FADE_TYPE type);
    void setPropertyAnimation(QByteArray, QVariant, QVariant, int,
                              QEasingCurve, QWidget*, QGraphicsEffect*, QWidget*);

protected:
#ifdef Q_OS_WIN32
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
#endif

    virtual void mousePressEvent(QMouseEvent *event);

    virtual void mouseMoveEvent(QMouseEvent *event);

    virtual void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void setColorScheme(COLOR_SCHEME mode);
    void on_Btn_mini_clicked();
    void on_Btn_close_clicked();
    void on_Btn_HomePage_clicked();
    void on_Btn_Settings_clicked();
    void on_Btn_Guide_clicked();
};
