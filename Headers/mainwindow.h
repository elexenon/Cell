#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Kits/DropShadowWidget.h"
#include "Kits/customFrame.h"

QT_BEGIN_NAMESPACE
namespace Ui { class mainWindow; }
QT_END_NAMESPACE

class GuideDialog;
class HomePageWidget;
class Workshop;
class SettingsPageWidget;
class QPushButton;

class mainWindow : public DropShadowWidget
{
    Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = nullptr);
    ~mainWindow();

// Pointers.
private:
    Ui::mainWindow         *ui;

    QList<QPushButton*>    *mainWindowTabBtns;
    QGraphicsOpacityEffect *opacityEffect;
    QPropertyAnimation     *propertyAnimi;

    Workshop            *workshop;
    HomePageWidget      *homePage;
    SettingsPageWidget  *settingsPage;
    GuideDialog         *guideDialog;

    customFrame         *frame_titleBar;


// Regular members;
private:
    QPoint m_startPoint;
    QPoint m_windowPoint;
    bool   m_move;
    PAGE_TYPE currentPage;
    COLOR_SCHEME m_mode;

private:
    void InitMainWindow();  
    void setAllTabsUnchecked();
    void startPageSwitchAnimation(PAGE_TYPE nextPage);
    void startFadeInOrOutAnimation(QWidget *target, int duration, FADE_TYPE type);

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
    void on_Btn_NewProject_clicked();
};
#endif
