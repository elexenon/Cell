// Copyright 2018-2019 CellTek.
//
// Distributed under the GPL License, Version 3.0.
//
// See accompanying file LICENSE.txt at the root
//
// Of source file directory.
#ifndef CUSTOMLINE_H
#define CUSTOMLINE_H

#include "customFrame.h"

class customLine : public customFrame{
    Q_OBJECT
    const QString BASEQSS;
public:
    enum LINESHAPE{
        _VERTICAL,
        _HORIZONTAL
    };
    explicit customLine(const QString &qss, QWidget *parent = nullptr, const LINESHAPE &shape = _HORIZONTAL);
    ~customLine() = default;

private:
    void Init();

    LINESHAPE shape;
};


#endif // CUSTOMLINE_H
