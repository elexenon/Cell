// Copyright 2018-2020 CellTek. < autologic@foxmail.com >
//
// This file may be used under the terms of the GNU General Public License
// version 3.0 as published by the free software foundation and appearing in
// the file LICENSE included in the packaging of this file.
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
