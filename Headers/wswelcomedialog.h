#ifndef WSWELCOMEDIALOG_H
#define WSWELCOMEDIALOG_H

#include <QDialog>
#include "Kits/DropShadowDialog.h"

namespace Ui {
class WSWelcomeDialog;
}

class WSWelcomeDialog : public DropShadowDialog
{
    Q_OBJECT

public:
    explicit WSWelcomeDialog(QWidget *parent = nullptr);
    ~WSWelcomeDialog();

public:
    void progress();

private:
    Ui::WSWelcomeDialog *ui;

    QTimer *timer;

private:
    QPoint  m_startPoint;
    QPoint  m_windowPoint;
    bool    m_move;

protected:
#ifdef Q_OS_WIN32
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
#endif

    virtual void    mousePressEvent(QMouseEvent *event);

    virtual void    mouseMoveEvent(QMouseEvent *event);

    virtual void    mouseReleaseEvent(QMouseEvent *event);

private slots:
    void updateProgressBar();
};

#endif // WSWELCOMEDIALOG_H
