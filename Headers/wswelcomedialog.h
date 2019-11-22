// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef WSWELCOMEDIALOG_H
#define WSWELCOMEDIALOG_H

#include <QDialog>
#include "Kits/customDialog.h" // Derived class

namespace Ui {
class WSWelcomeDialog;
}

class WSWelcomeDialog : public customDialog
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

private slots:
    void updateProgressBar();
};

#endif // WSWELCOMEDIALOG_H
