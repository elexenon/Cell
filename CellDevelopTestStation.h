#ifndef CELLDEVELOPTESTSTATION_H
#define CELLDEVELOPTESTSTATION_H

#include <QWidget>

namespace Ui {
class CellDevelopTestStation;
}

class CellDevelopTestStation : public QWidget
{
    Q_OBJECT

public:
    explicit CellDevelopTestStation(QWidget *parent = nullptr);
    ~CellDevelopTestStation();

private:
    Ui::CellDevelopTestStation *ui;
};

#endif // CELLDEVELOPTESTSTATION_H
