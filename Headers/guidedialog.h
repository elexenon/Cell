#ifndef GUIDEDIALOG_H
#define GUIDEDIALOG_H

#include <QDialog>
#include "Headers/_utility.h"

namespace Ui {
class GuideDialog;
}

class GuideDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GuideDialog(QWidget *parent = nullptr);
    ~GuideDialog();

private:
    Ui::GuideDialog *ui;
    QFile           *styleSheetLoader;

private:
    QPoint  m_startPoint;
    QPoint  m_windowPoint;
    bool    m_move;
    QString myStyleSheet;

private:
    void Init();
    void setMyStyleSheet(QString name);

protected:
#ifdef Q_OS_WIN32
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
#endif

    virtual void    mousePressEvent(QMouseEvent *event);

    virtual void    mouseMoveEvent(QMouseEvent *event);

    virtual void    mouseReleaseEvent(QMouseEvent *event);
private slots:
    void on_Btn_close_clicked();
};

#endif // GUIDEDIALOG_H
