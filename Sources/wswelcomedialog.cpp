// Copyright 2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#include <QTimer>

#include "ui_wswelcomedialog.h"
#include "Headers/wswelcomedialog.h"
#include "Headers/Kits/cell_util.h"

WSWelcomeDialog::WSWelcomeDialog(QWidget *parent) :
    DropShadowDialog(parent),
    ui(new Ui::WSWelcomeDialog),
    timer(new QTimer)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
#ifdef Q_OS_WIN32
    DropShadowDialog::LoadWinStyle(this);
#endif
    setAutoFillBackground(true);
    setModal(true);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateProgressBar()));
}

WSWelcomeDialog::~WSWelcomeDialog()
{
    delete ui;
}

void WSWelcomeDialog::progress()
{
    timer->start(10);
}

void WSWelcomeDialog::updateProgressBar()
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
// Achieve the window drop shadow effect( Windows ).
bool WSWelcomeDialog::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    return DropShadowDialog::nativeEvent(eventType, message, result);
}
#endif
