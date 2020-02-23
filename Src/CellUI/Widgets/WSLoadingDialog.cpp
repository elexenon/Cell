// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
#include <QTimer>

#include "ui_WSLoadingDialog.h"
#include "WSLoadingDialog.h"
#include "../../CellCore/Kits/CellUtility.h"

WSLoadingDialog::WSLoadingDialog(QWidget *parent) :
    customWinstyleDialog(parent),
    ui(new Ui::WSLoadingDialog),
    timer(new QTimer(this))
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
    if(bar->value() < 95)
        bar->setValue(bar->value()+2);
    else{
        timer->stop();
        close();
    }
}
