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
    customWinstyleDialog(parent),
    ui(new Ui::WSLoadingDialog),
    timer(new QTimer)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose);
    customWinstyleDialog::LoadWinStyle(this);
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
