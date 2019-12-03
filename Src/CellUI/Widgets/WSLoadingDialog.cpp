// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include <QTimer>

#include "ui_WSLoadingDialog.h"
#include "WSLoadingDialog.h"
#include "../../CellCore/Kits/CellUtility.h"

WSLoadingDialog::WSLoadingDialog(QWidget *parent) :
    customDialog(parent),
    ui(new Ui::WSLoadingDialog),
    timer(new QTimer)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
#ifdef Q_OS_WIN32
    customDialog::LoadWinStyle(this);
#endif
    setAutoFillBackground(true);
    setModal(true);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateProgressBar()));
}

WSLoadingDialog::~WSLoadingDialog()
{
    delete ui;
}

void WSLoadingDialog::progress()
{
    timer->start(10);
}

void WSLoadingDialog::updateProgressBar()
{
    QProgressBar *bar = ui->progressBar;
    if(bar->value() < 100)
        bar->setValue(bar->value()+1);
    else{
        timer->stop();
        delete timer;
        close();
    }
}

#ifdef Q_OS_WIN32
bool WSLoadingDialog::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    return customDialog::nativeEvent(eventType, message, result);
}
#endif
