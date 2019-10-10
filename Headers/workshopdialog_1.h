#ifndef WORKSHOPDIALOG_1_H
#define WORKSHOPDIALOG_1_H

#include <QDialog>
#include "Kits/_utility.h"

namespace Ui {
class WorkshopDialog_1;
}

class WorkshopDialog_1 : public QDialog
{
    Q_OBJECT

public:
    explicit WorkshopDialog_1(QWidget *parent = nullptr);
    ~WorkshopDialog_1();

private:
    Ui::WorkshopDialog_1 *ui;

private:
    void Init();
};

#endif // WORKSHOPDIALOG_1_H
