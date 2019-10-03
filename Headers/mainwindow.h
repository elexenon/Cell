#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "Headers/_utility.h"

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

private:
    Ui::mainWindow *ui;
    QPoint          m_startPoint;
    QPoint          m_windowPoint;
    bool            m_move;
    QFile          *styleSheetLoader;
    QString         myStyleSheet;
    bool            isMaxSize;

private:
    void            setMyStyleSheet(QString name);

protected:
#ifdef Q_OS_WIN32
      virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
#endif

    virtual void    mousePressEvent(QMouseEvent *event);

    virtual void    mouseMoveEvent(QMouseEvent *event);

    virtual void    mouseReleaseEvent(QMouseEvent *event);

    virtual void    paintEvent(QPaintEvent *e);
private slots:
    void            on_Btn_mini_clicked();
    void            on_Btn_max_clicked();
    void            on_Btn_close_clicked();
};
#endif // MAINWINDOW_H
