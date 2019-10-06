#pragma once

#include "_utility.h"
#include "guidedialog.h"
#include "qstylesheetloader.h"
#include "homepagewidget.h"
#include "settingspagewidget.h"
//#define ROUNDED_WINDOW

QT_BEGIN_NAMESPACE
namespace Ui { class mainWindow; }
QT_END_NAMESPACE

#ifdef Q_OS_WIN32
#include "DropShadowWidget.h"
#endif

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
#ifdef ROUNDED_WINDOW
    virtual void paintEvent(QPaintEvent *e);
#endif
private slots:
    void on_Btn_mini_clicked();
    void on_Btn_close_clicked();
    void on_Btn_HomePage_clicked();
    void on_Btn_Settings_clicked();
    void on_Btn_Guide_clicked();
};
