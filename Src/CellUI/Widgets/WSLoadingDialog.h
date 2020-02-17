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
#include "../CustomBaseWidgets/customWinstyleDialog.h" // Derived class

namespace Ui {
class WSLoadingDialog;
}

class WSLoadingDialog : public customWinstyleDialog
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

private Q_SLOTS:
    void updateProgressBar();
};

#endif // WSLoadingDialog_H
