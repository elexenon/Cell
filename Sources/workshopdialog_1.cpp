#include "Headers/workshopdialog_1.h"
#include "ui_workshopdialog_1.h"

WorkshopDialog_1::WorkshopDialog_1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorkshopDialog_1)
{
    ui->setupUi(this);
    Init();
}

WorkshopDialog_1::~WorkshopDialog_1()
{
    delete ui;
}

void WorkshopDialog_1::Init()
{
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
}
