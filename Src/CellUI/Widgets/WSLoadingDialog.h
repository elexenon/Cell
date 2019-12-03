// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef WSLoadingDialog_H
#define WSLoadingDialog_H

#include <QDialog>
#include "../CustomBaseWidgets/customDialog.h" // Derived class

namespace Ui {
class WSLoadingDialog;
}

class WSLoadingDialog : public customDialog
{
    Q_OBJECT

public:
    explicit WSLoadingDialog(QWidget *parent = nullptr);
    ~WSLoadingDialog();

public:
    void progress();

private:
    Ui::WSLoadingDialog *ui;

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

#endif // WSLoadingDialog_H
