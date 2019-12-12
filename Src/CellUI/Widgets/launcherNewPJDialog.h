#ifndef LAUNCHERNEWPJDIALOG_H
#define LAUNCHERNEWPJDIALOG_H

#include <QDialog>

#include "../../CellCore/Kits/CellUtility.h"    // COLOR_SCHEME
#include "../CustomBaseWidgets/customDialog.h"

class customFrame;
class customLabel;
class QPropertyAnimation;

namespace Ui {
class LauncherNewPJDialog;
}

class LauncherNewPJDialog : public customDialog
{
    Q_OBJECT

public:
    explicit LauncherNewPJDialog(QWidget *parent = nullptr);
    ~LauncherNewPJDialog();

private:
    Ui::LauncherNewPJDialog *ui;

private:
    QPropertyAnimation *label_animi;

    customFrame *frame_titleBar;
    customLabel *label_choose;

    QPoint  m_startPoint;
    QPoint  m_windowPoint;
    bool    m_move;

private:
    void Init();

private:
    CellGlobal::COLOR_SCHEME m_mode;

protected:
#ifdef Q_OS_WIN32
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
#endif

    virtual void mousePressEvent(QMouseEvent *event);

    virtual void mouseMoveEvent(QMouseEvent *event);

    virtual void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void setColorScheme(CellGlobal::COLOR_SCHEME mode)
};

#endif // LAUNCHERNEWPJDIALOG_H
