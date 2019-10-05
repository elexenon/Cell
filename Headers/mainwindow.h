#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "Headers/_utility.h"
#include "guidedialog.h"
#include "Headers/qstylesheetloader.h"
//#define ROUNDED_WINDOW

QT_BEGIN_NAMESPACE
namespace Ui { class mainWindow; }
QT_END_NAMESPACE

class mainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = nullptr);
    ~mainWindow();

public:
    void InitMainWindow();

// Pointers.
private:
    Ui::mainWindow      *ui;
    GuideDialog         *guideDialog;
    QList<QPushButton*> *mainWindowTabBtns;
    QStyleSheetLoader   *styleSheetLoader;

// Regular members;
private:
    QPoint          m_startPoint;
    QPoint          m_windowPoint;
    bool            m_move;

private:
    void            setAllTabsUnchecked();

protected:
#ifdef Q_OS_WIN32
      virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
#endif

    virtual void    mousePressEvent(QMouseEvent *event);

    virtual void    mouseMoveEvent(QMouseEvent *event);

    virtual void    mouseReleaseEvent(QMouseEvent *event);
#ifdef ROUNDED_WINDOW
    virtual void    paintEvent(QPaintEvent *e);
#endif
private slots:
    void on_Btn_mini_clicked();
    void on_Btn_close_clicked();
    void on_Btn_HomePage_clicked();
    void on_Btn_Settings_clicked();
    void on_Btn_Guide_clicked();
};
#endif // MAINWINDOW_H
